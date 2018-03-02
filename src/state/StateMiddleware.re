/**
 * A convenience function to make un-curried middleware creation for Redux easier
 */
let makeMiddleware = (~handler) =>
  [@bs] ((store) => [@bs] ((next) => [@bs] ((action) => handler(~store, ~next, ~action))));

let handleActors = (~actors) =>
  makeMiddleware(
    ~handler=
      (~store, ~next, ~action) => {
        let (dispatch, getState) = (store##dispatch, store##getState);
        let result = [@bs] next(action);
        actors |> Js.Array.forEach((actor) => actor(~action, ~dispatch, ~getState));
        result
      }
  );
