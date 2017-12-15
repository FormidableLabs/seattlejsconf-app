open ReactNative;

let component = ReasonReact.statelessComponent("CloseButton");

let styles =
  StyleSheet.create(
    Style.(
      {
        "text":
          style([
            fontFamily("open-sans"),
            fontSize(18.),
            color("white"),
            textAlign(`center),
            backgroundColor("transparent")
          ]),
        "button":
          style([
            backgroundColor("rgb(140, 170, 29)"),
            padding(10.),
            margin(10.),
            borderRadius(24.),
            flex(0.)
          ])
      }
    )
  );

let make = (~onPress, _children) => {
  ...component,
  render: (_self) =>
    <TouchableOpacity onPress>
      <View style=styles##button> <Text style=styles##text value="Close" /> </View>
    </TouchableOpacity>
};