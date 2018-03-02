open BsAbstract;

let toOption = Js.Nullable.toOption;

let (getWithDefault, some) = Js.Option.(getWithDefault, some);


/***
 * Types
 */
[@bs.deriving jsConverter]
type eventType = [ [@bs.as "DEFAULT"] | `DEFAULT [@bs.as "MEETUP"] | `MEETUP];

/**
 * The event type used in the Redux store
 */
type event = {
  .
  "id": option(string),
  "createdAt": option(Js.Date.t),
  "updatedAt": option(Js.Date.t),
  "date": Js.Date.t,
  "description": option(string),
  "eventType": eventType,
  "location": option(string),
  "name": string,
  "owner": option({. "headline": option(string), "id": string, "name": option(string)})
};

let fromResponse = (input) : event => {
  "id": input##id |> Js.Json.decodeString,
  "createdAt": input##createdAt |> Utils.decodeDate,
  "updatedAt": input##updatedAt |> Utils.decodeDate,
  "date": input##date |> Utils.decodeDate |> getWithDefault(Js.Date.make()),
  "description": input##description,
  "eventType": input##eventType,
  "location": input##location,
  "name": input##name,
  "owner":
    Option.Infix.(
      input##owner
      <#> (
        (owner) => {
          "id": owner##id |> Js.Json.decodeString |> getWithDefault(""),
          "headline": owner##headline,
          "name": owner##name
        }
      )
    )
};

let toInput = (event: event) => {
  "id": Option.Infix.(event##id <#> Js.Json.string),
  "createdAt": Option.Infix.(event##createdAt <#> Utils.encodeDate),
  "updatedAt": Option.Infix.(event##updatedAt <#> Utils.encodeDate),
  "date": event##date |> Utils.encodeDate,
  "description": event##description,
  "eventType": event##eventType,
  "location": event##location,
  "name": event##name,
  "owner":
    Option.Infix.(
      event##owner
      <#> Json.Encode.(
            (owner) =>
              object_([
                ("id", owner##id |> string),
                ("headline", owner##headline |> nullable(string)),
                ("name", owner##name |> nullable(string))
              ])
          )
    )
};


/***
 * Queries & Mutations
 */
module EventById = [%graphql
  {|
    query EventById($id: UUID!) {
      eventById(id: $id) {
        id
        createdAt
        updatedAt
        name
        date
        eventType
        location
        description
        owner: userByOwner {
          id
          name
          headline
        }
      }
    }
  |}
];

module AllEvents = [%graphql
  {|
    query AllEvents(
      $first: Int
      $last: Int
      $offset: Int
      $before: Cursor
      $after: Cursor
      $orderBy: [EventsOrderBy!] = [PRIMARY_KEY_ASC]
      $condition: EventCondition
    ) {
      allEvents(
        first: $first
        last: $last
        offset: $offset
        before: $before
        after: $after
        orderBy: $orderBy
        condition: $condition
      ) {
        edges {
          node {
            id
            createdAt
            updatedAt
            name
            date
            eventType
            location
            description
            owner: userByOwner {
              id
              name
              headline
            }
          }
        }
      }
    }
  |}
];

module CreateEvent = [%graphql
  {|
    mutation CreateEvent($input: CreateEventInput!) {
      createEvent(input: $input) {
        event {
          id
          createdAt
          updatedAt
          name
          date
          eventType
          location
          description
          owner: userByOwner {
            id
            name
            headline
          }
        }
      }
    }
  |}
];


/***
 * JS interface
 */
type input = {
  .
  "clientMutationId": Js.Nullable.t(string),
  "event": {
    .
    "id": Js.Nullable.t(string),
    "createdAt": Js.Nullable.t(float),
    "updatedAt": Js.Nullable.t(float),
    "name": string,
    "date": float,
    "eventType": string,
    "location": Js.Nullable.t(string),
    "description": Js.Nullable.t(string),
    "owner": Js.Nullable.t(string)
  }
};

let fromJs = (input) =>
  Option.Infix.(
    {
      "clientMutationId": input##clientMutationId |> toOption,
      "event": {
        "id": input##event##id |> toOption <#> Js.Json.string,
        "createdAt": input##event##createdAt |> toOption <#> Js.Json.number,
        "updatedAt": input##event##updatedAt |> toOption <#> Js.Json.number,
        "name": input##event##name,
        "date": input##event##date |> Js.Json.number,
        "eventType": input##event##eventType |> eventTypeFromJs |> getWithDefault(`DEFAULT),
        "location": input##event##location |> toOption,
        "description": input##event##description |> toOption,
        "owner": input##event##owner |> toOption <#> Js.Json.string
      }
    }
  );

let eventById = [@bs] ((id) => ApiClient.(client |> query(~request=EventById.make(~id, ()))));

let allEvents = [@bs] (() => ApiClient.(client |> query(~request=AllEvents.make())));

let createEvent =
  [@bs]
  (
    (input: input) =>
      ApiClient.(client |> mutate(~request=CreateEvent.make(~input=fromJs(input), ())))
  );
