type selection = {
  .
  "alias": string,
  "arguments": Js.Array.t(string),
  "directives": Js.Array.t(string),
  "kind": string,
  "name": {
    .
    "kind": string,
    "value": string
  },
  "selectionSet": {
    .
    "kind": string,
    "selections": Js.Array.t(selection)
  }
};

type definition = {
  .
  "directives": Js.Array.t(string),
  "name": {
    .
    "kind": string,
    "value": string
  },
  "operation": string,
  "selectionSet": {
    .
    "kind": string,
    "selections": Js.Array.t(selection)
  },
  "loc": {
    .
    "_end": int,
    "start": int
  },
  "kind": string
};

type definitions = Js.Array.t(definition);

[@bs.module "graphql-tag"] external _gql : string => definitions = "default";

let gql = (query) => _gql(query);
