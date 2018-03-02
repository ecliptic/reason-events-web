open Mnstr;

let (query, mutate) = Client.(query, mutate);

let client =
  Client.make(
    ~uri=Config.Api.endpoint,
    ~getSession=Client.BrowserSession.get,
    ~connectToDevTools=Config.Env.isDev ? Js.true_ : Js.false_,
    ()
  );
