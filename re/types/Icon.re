[@bs.module "@expo/vector-icons"] external icons : ReasonReact.reactClass = "EvilIcons";

let make = (~name: string, ~size: int, ~color: string, ~style=?, children) =>
  ReasonReact.wrapJsForReason(
    ~reactClass=icons,
    ~props={"name": name, "size": size, "color": color, "style": style},
    children
  );
