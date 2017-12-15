type hoc = ReasonReact.reactClass => ReasonReact.reactClass;

[@bs.module "react-apollo"] external graphql : GraphQLTag.definitions => hoc = "graphql";

module type Query = {type data; let query: GraphQLTag.definitions;};

module CreateWrapper = (Query: Query) => {
  type props = {. "data": Query.data};
  let wrapComponent = (~component, ~make) => {
    let jsComponent =
      ReasonReact.wrapReasonForJs(
        ~component,
        (props: props) => {
          let data = props##data;
          make(~data, [||])
        }
      );
    graphql(Query.query, jsComponent)
  };
};
