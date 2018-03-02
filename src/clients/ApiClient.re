open Mnstr;

let (query, mutate) = ApiClient.(query, mutate);

let client =
  ApiClient.make(
    ~uri=Config.Api.endpoint,
    ~getSession=ClientSession.get,
    ~connectToDevTools=Config.Env.isDev ? Js.true_ : Js.false_,
    ()
  );
