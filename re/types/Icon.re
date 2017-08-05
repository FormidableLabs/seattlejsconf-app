external icons : ReasonReact.reactClass = "EvilIcons" [@@bs.module "@expo/vector-icons"];

let make name::(name: string) size::(size: int) color::(color: string) ::style=? children =>
  ReasonReact.wrapJsForReason
    reactClass::icons props::{"name": name, "size": size, "color": color, "style": style} children;
