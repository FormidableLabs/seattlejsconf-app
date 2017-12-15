open ReactNative;

let component = ReasonReact.statelessComponent("SponsorTitle");

let styles =
  StyleSheet.create(
    Style.(
      {
        "titleWrap": style([paddingVertical(10.), marginHorizontal(10.)]),
        "sponsorTitle":
          style([
            fontFamily("montserrat-bold"),
            fontSize(18.),
            color("white"),
            textAlign(`center),
            backgroundColor("transparent")
          ])
      }
    )
  );

let make = (~value, _children) => {
  ...component,
  render: (_self) =>
    <View style=styles##titleWrap> <Text value style=styles##sponsorTitle /> </View>
};
