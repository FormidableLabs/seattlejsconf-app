type selection =
  Js.t {
    .
    alias : string,
    arguments : Js.Array.t string,
    directives : Js.Array.t string,
    kind : string,
    name : Js.t {. kind : string, value : string},
    selectionSet : Js.t {. kind : string, selections : Js.Array.t selection}
  };

type definition =
  Js.t {
    .
    directives : Js.Array.t string,
    name : Js.t {. kind : string, value : string},
    operation : string,
    selectionSet : Js.t {. kind : string, selections : Js.Array.t selection},
    loc : Js.t {. _end : int, start : int},
    kind : string
  };

type definitions = Js.Array.t definition;

external _gql : string => definitions = "default" [@@bs.module "graphql-tag"];

let gql query => _gql query;
