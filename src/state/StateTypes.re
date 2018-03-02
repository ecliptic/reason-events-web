type reAction = ..;

module Users = {
  type user = UserData.user;
  type state = {. "user": option(user)};
  type reAction +=
    | SetUser (user);
};

module Events = {
  type event = EventData.event;
  type state = {. "items": array(event)};
  type reAction +=
    | RefreshEvents
    | SetEvents (array(event))
    | CreateEvent (event);
};

type action = {. "type": string, "reAction": reAction};

type state = {. "users": {.}, "events": Events.state};
