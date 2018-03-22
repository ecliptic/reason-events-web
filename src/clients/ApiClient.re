let (query, mutate) = MnstrClient.(query, mutate);

let client =
  MnstrClient.(
    make(
      ~uri=Config.Api.endpoint,
      ~getSession=Browser.Session.get,
      ~connectToDevTools=Config.Env.isDev ? Js.true_ : Js.false_,
      ()
    )
  );
