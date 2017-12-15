type region = {
  .
  "latitude": float, "longitude": float, "latitudeDelta": float, "longitudeDelta": float
};

[@bs.module "expo"] external mapview : ReasonReact.reactClass = "MapView";

let option_map = (fn, opt_value) =>
  switch opt_value {
  | None => None
  | Some(value) => Some(fn(value))
  };

let make = (~initialRegion: region, ~style=?, children) =>
  ReasonReact.wrapJsForReason(
    ~reactClass=mapview,
    ~props={"initialRegion": initialRegion, "style": style},
    children
  );

module Marker = {
  type latLng = {. "latitude": float, "longitude": float};
  type rawImageSourceJS;
  external rawImageSourceJS : 'a => rawImageSourceJS = "%identity";
  [@bs.module "expo"] [@bs.scope "MapView"] external marker : ReasonReact.reactClass = "Marker";
  let make = (~coordinate: latLng, ~title: string, ~image=?, children) =>
    ReasonReact.wrapJsForReason(
      ~reactClass=marker,
      ~props={
        "coordinate": coordinate,
        "title": title,
        "image": Js.Undefined.from_opt(option_map(rawImageSourceJS, image))
      },
      children
    );
};