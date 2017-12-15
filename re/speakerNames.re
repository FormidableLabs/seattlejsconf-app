open ReactNative;

let component = ReasonReact.statelessComponent("SpeakerNames");

let styles =
  StyleSheet.create(
    Style.(
      {
        "speaker":
          style([
            fontFamily("montserrat"),
            fontSize(16.),
            letterSpacing(1.),
            color("rgb(185,219,111)"),
            marginBottom(6.)
          ])
      }
    )
  );

let make = (~talk: Item.talk, _children) => {
  ...component,
  render: (_self) =>
    <Text style=styles##speaker>
      (
        Array.mapi(
          (i, {Item.name}) =>
            i > 0 ?
              ReasonReact.stringToElement(String.uppercase(" & " ++ name)) :
              ReasonReact.stringToElement(String.uppercase(name)),
          talk.speakers
        )
        |> ReasonReact.arrayToElement
      )
    </Text>
};
