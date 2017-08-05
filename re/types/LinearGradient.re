external linearGradient : ReasonReact.reactClass = "LinearGradient" [@@bs.module "expo"];

let make colors::(colors: array string) ::style=? children =>
  ReasonReact.wrapJsForReason
    reactClass::linearGradient props::{"colors": colors, "style": style} children;
