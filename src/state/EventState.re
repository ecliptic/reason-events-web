open BsAbstract;

open StateTypes;

let toOption = Js.Nullable.toOption;

let getWithDefault = Js.Option.getWithDefault;

let (assign, empty) = Js.Obj.(assign, empty);

let prefix = "EVENTS";

let actionTypes = {
  "setEvents": prefix ++ ":SET_EVENTS",
  "refreshEvents": prefix ++ ":REFRESH_EVENTS",
  "createEvent": prefix ++ ":CREATE_EVENT"
};

let actions = {
  "setEvents": (events) => {"type": actionTypes##setEvents, "reAction": Events.SetEvents(events)},
  "refreshEvents": () => {"type": actionTypes##refreshEvents, "reAction": Events.RefreshEvents},
  "createEvent": (event) => {
    "type": actionTypes##createEvent,
    "reAction": Events.CreateEvent(event)
  }
};

let initialState: Events.state = {"items": [||]};

let reducer = (state, action) => {
  let state = state |> toOption |> getWithDefault(initialState);
  switch (action##reAction |> toOption) {
  | Some(Events.SetEvents(events)) => assign(empty()) @@ assign(state) @@ {"items": events}
  | _ => state
  }
};

let select = {"events": fun (state: state) => (state##events##items: array(EventData.event))};

let setEventsFromResponse = (~dispatch, response) => {
  let setEvents = actions##setEvents;
  switch response##parsed##allEvents {
  | Some(events) =>
    events##edges
    |> Js.Array.map((edge) => edge##node)
    |> Js.Array.map(EventData.fromResponse)
    |> setEvents
    |> dispatch
  | None => ()
  };
  Js.Promise.resolve()
};

let setNewEventFromResponse = (~dispatch, ~getState, response) => {
  open Option.Infix;
  let setEvents = actions##setEvents;
  let selectEvents = select##events;
  switch (response##parsed##createEvent >>= ((input) => input##event)) {
  | Some(event) =>
    let events = selectEvents(getState());
    dispatch(setEvents(events |> Js.Array.concat([|EventData.fromResponse(event)|])))
  | None => ()
  };
  Js.Promise.resolve()
};

let eventManagement = (~action, ~dispatch, ~getState) =>
  PromiseUtils.Infix.(
    switch (action##reAction |> toOption) {
    /* Refresh events */
    | Some(Events.RefreshEvents) =>
      ApiClient.(
        client
        |> query(~request=EventData.AllEvents.make())
        >>= setEventsFromResponse(~dispatch)
        |> ignore
      )
    /* Create a new event */
    | Some(Events.CreateEvent(event)) =>
      ApiClient.(
        client
        |> mutate(
             ~request=
               EventData.CreateEvent.make(
                 ~input={"event": EventData.toInput(event), "clientMutationId": None},
                 ()
               )
           )
        >>= setNewEventFromResponse(~dispatch, ~getState)
        |> ignore
      )
    | _ => ()
    }
  );
