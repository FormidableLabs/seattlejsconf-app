[@bs.module "expo"] external linearGradient : ReasonReact.reactClass = "LinearGradient";

let make = (~colors: array(string), ~style=?, children) =>
  ReasonReact.wrapJsForReason(
    ~reactClass=linearGradient,
    ~props={"colors": colors, "style": style},
    children
  );
