open ReactNative;

let component = ReasonReact.statelessComponent("TalkDescription");

let styles =
  StyleSheet.create(
    Style.(
      {
        "wrapper": style([padding(10.), marginTop(-10.)]),
        "text": style([fontFamily("open-sans"), fontSize(16.), color("white")])
      }
    )
  );

let make = (~value, _children) => {
  ...component,
  render: (_self) =>
    <View style=styles##wrapper>
      <Text style=styles##text> (ReasonReact.stringToElement(value)) </Text>
    </View>
};
