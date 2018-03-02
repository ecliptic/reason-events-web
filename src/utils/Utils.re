open BsAbstract;

let getWithDefault = Js.Option.getWithDefault;

[@bs.module "he"] external decodeEntities : string => string = "decode";

[@bs.val] external parseInt_ : (string, int) => int = "parseInt";

/** parseInt with an assumed radix of 10 */
let parseInt = (string) => parseInt_(string, 10);

let displayIf = (option, render) =>
  switch option {
  | Some(value) => render(value)
  | None => ReasonReact.nullElement
  };

let displayIfBool = (bool, render) =>
  if (bool) {
    render()
  } else {
    ReasonReact.nullElement
  };

let (<?>) = displayIf;

module Obj = {
  [@bs.module "lodash"] external get_ : [@bs] ((Js.t('a), string) => Js.Nullable.t('b)) = "get";
  [@bs.module "lodash"]
  external mapKeys_ : [@bs] ((Js.t('a), ('b, string) => string) => Js.t('c)) =
    "mapKeys";
  [@bs.module] external toSnakeCase : string => string = "to-snake-case";
  let get = (path, obj) => [@bs] get_(obj, path) |> Js.Nullable.toOption;
};

let snakecaseKeys = (obj) => [@bs] Obj.mapKeys_(obj, (_value, key) => Obj.toSnakeCase(key));

let decodeDate = (date) =>
  Option.Infix.(date |> Js.Json.decodeString <#> Js.Date.fromString);

let encodeDate = (date) => date |> Js.Date.toString |> Js.Json.string;
