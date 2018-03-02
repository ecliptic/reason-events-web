let (getWithDefault, some) = Js.Option.(getWithDefault, some);

type user = {
  .
  "id": string,
  "email": option(string),
  "headline": option(string),
  "mailingList": option(Js.boolean),
  "name": option(string)
};

let fromResponse = (input) : user => {
  "id": input##id |> Js.Json.decodeString |> getWithDefault(""),
  "email": input##email,
  "headline": input##headline,
  "mailingList": input##mailingList,
  "name": input##name
};

let toInput = (user: user) => {
  "id": user##id |> Js.Json.string |> some,
  "email": user##email,
  "headline": user##headline,
  "mailingList": user##mailingList,
  "name": user##name
};

module UserById = [%graphql
  {|
    query UserById($id: UUID!) {
      userById(id: $id) {
        id
        name
        email
        headline
        mailingList
      }
    }
  |}
];

/**
 * Plain JS interface
 */
let userById = [@bs] ((id) => ApiClient.(client |> query(~request=UserById.make(~id, ()))));
