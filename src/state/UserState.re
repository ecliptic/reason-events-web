open StateTypes;

let toOption = Js.Nullable.toOption;

let getWithDefault = Js.Option.getWithDefault;

let (assign, empty) = Js.Obj.(assign, empty);

let prefix = "USERS";

let actionTypes = {"setUser": prefix ++ ":SET_USER"};

let actions = {
  "setUser": (user) => {"type": actionTypes##setUser, "reAction": Users.SetUser(user)}
};

let initialState: Users.state = {"user": None};

let reducer = (state, action) => {
  let state = state |> toOption |> getWithDefault(initialState);
  switch (action##reAction |> toOption) {
  | Some(Users.SetUser(user)) => {"user": user} |> assign(state) |> assign(empty())
  | _ => state
  }
};

let select = {"events": fun (state: state) => (state##events##items: array(EventData.event))};

let actors = [||];
