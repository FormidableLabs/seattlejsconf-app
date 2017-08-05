external touchable : ReasonReact.reactClass =
  "default" [@@bs.module "react-native-platform-touchable"];

let make ::onPress=? ::delayPressIn=? ::style=? children =>
  ReasonReact.wrapJsForReason
    reactClass::touchable
    props::
      Js.Undefined.(
        {
          "onPress": from_opt onPress,
          "delayPressIn": from_opt delayPressIn,
          "style": from_opt style
        }
      )
    children;
