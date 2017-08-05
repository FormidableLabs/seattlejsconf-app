type hoc = ReasonReact.reactClass => ReasonReact.reactClass;

external _graphql : GraphQLTag.definitions => hoc = "graphql" [@@bs.module "react-apollo"];

let graphql ::query => _graphql query;
