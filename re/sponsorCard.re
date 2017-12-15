open ReactNative;

let component = ReasonReact.statelessComponent("SponsorTitle");

let styles =
  StyleSheet.create(
    Style.(
      {
        "card":
          style([
            flex(0.),
            backgroundColor("white"),
            padding(20.),
            marginHorizontal(20.),
            marginVertical(10.),
            overflow(`hidden)
          ]),
        "imageContain": style([flex(1.), overflow(`hidden), maxHeight(100.)]),
        "logo": style([widthPct(90.), alignSelf(`center), maxHeight(100.), overflow(`hidden)]),
        "description":
          style([
            fontFamily("open-sans"),
            fontSize(16.),
            color("black"),
            textAlign(`left),
            backgroundColor("transparent"),
            marginVertical(10.)
          ])
      }
    )
  );

let make = (~logo, ~url, ~description=?, _children) => {
  ...component,
  render: (_self) =>
    <TouchableOpacity onPress=((_) => Link.openURL(url))>
      <View style=styles##card>
        <View style=styles##imageContain>
          <Image source=logo style=styles##logo resizeMode=`contain />
        </View>
        (
          switch description {
          | None => ReasonReact.nullElement
          | Some(d) => <Text value=d style=styles##description />
          }
        )
      </View>
    </TouchableOpacity>
};
