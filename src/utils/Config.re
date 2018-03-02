let getEnvVar = (key, fallback) =>
  Js.Option.getWithDefault(fallback, Js.Dict.get([%bs.raw {|process.env|}], key));

module Env = {
  let isDev = getEnvVar("NODE_ENV", "production") === "development";
  let isBrowser: bool = [%raw {|typeof window !== "undefined"|}] |> Js.to_bool;
};

module Api = {
  let endpoint =
    getEnvVar("GATSBY_API_ENDPOINT", "http://localhost:4000/graphql");
};
