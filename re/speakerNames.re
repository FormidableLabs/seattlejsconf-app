open ReactNative;

let component = ReasonReact.statelessComponent "SpeakerNames";

let styles =
  StyleSheet.create
    Style.(
      {
        "speaker":
          style [
            fontFamily "montserrat",
            fontSize 16.,
            letterSpacing 1.,
            color "rgb(185,219,111)",
            marginBottom 6.
          ]
      }
    );

let make ::talk _children => {
  ...component,
  render: fun _self =>
    <Text style=styles##speaker>
      (
        Array.mapi
          (
            fun i s =>
              i > 0 ?
                ReasonReact.stringToElement (String.uppercase (" & " ^ s##name)) :
                ReasonReact.stringToElement (String.uppercase s##name)
          )
          talk##speakers |> ReasonReact.arrayToElement
      )
    </Text>
};
