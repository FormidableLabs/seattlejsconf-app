open ReactNative;

let component = ReasonReact.statelessComponent("SpeakerBio");

let styles =
  StyleSheet.create(
    Style.(
      {
        "wrapper": style([padding(10.), marginTop(-10.)]),
        "heading":
          style([color("rgb(185,219,111)"), fontSize(16.), marginBottom(5.), marginTop(5.)]),
        "text": style([fontFamily("open-sans"), fontSize(16.), color("white")])
      }
    )
  );

let make = (~speakers: array(Item.speaker), _children) => {
  ...component,
  render: (_self) => {
    let speakerCount = Array.length(speakers);
    speakerCount > 1 ?
      <View>
        (
          Array.map(
            ({Item.bio, name}) =>
              <View style=styles##wrapper key=name>
                <Text value=name style=styles##heading />
                <Text style=styles##text value=bio />
              </View>,
            speakers
          )
          |> ReasonReact.arrayToElement
        )
      </View> :
      <View style=styles##wrapper>
        <Text value="Speaker Bio" style=styles##heading />
        <Text style=styles##text value=speakers[0].bio />
      </View>
  }
};
