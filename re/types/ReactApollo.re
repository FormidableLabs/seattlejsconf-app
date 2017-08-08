type hoc = ReasonReact.reactClass => ReasonReact.reactClass;

external graphql : GraphQLTag.definitions => hoc = "graphql" [@@bs.module "react-apollo"];

module type Query = {type data; let query: GraphQLTag.definitions;};

module CreateWrapper (Query: Query) => {
  type props = Js.t {. data : Query.data};
  let wrapComponent ::component ::make => {
    let jsComponent =
      ReasonReact.wrapReasonForJs
        ::component
        (
          fun (props: props) => {
            let data = props##data;
            make ::data [||]
          }
        );
    graphql Query.query jsComponent
  };
};