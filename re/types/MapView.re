type region =
  Js.t {. latitude : float, longitude : float, latitudeDelta : float, longitudeDelta : float};

external mapview : ReasonReact.reactClass = "MapView" [@@bs.module "expo"];

let make initialRegion::(initialRegion: region) ::style=? children =>
  ReasonReact.wrapJsForReason
    reactClass::mapview props::{"initialRegion": initialRegion, "style": style} children;

module Marker = {
  type latLng = Js.t {. latitude : float, longitude : float};
  type rawImageSourceJS;
  external rawImageSourceJS : 'a => rawImageSourceJS = "%identity";
  external marker : ReasonReact.reactClass = "Marker" [@@bs.module "expo"] [@@bs.scope "MapView"];
  let make coordinate::(coordinate: latLng) title::(title: string) ::image=? children =>
    ReasonReact.wrapJsForReason
      reactClass::marker
      props::{
        "coordinate": coordinate,
        "title": title,
        "image": Js.Undefined.from_opt (UtilsRN.option_map rawImageSourceJS image)
      }
      children;
};
