open ReactNative;

let component = ReasonReact.statelessComponent "SpeakerBio";

let styles =
  StyleSheet.create
    Style.(
      {
        "wrapper": style [padding 10., marginTop (-10.)],
        "heading": style [color "rgb(185,219,111)", fontSize 16., marginBottom 5., marginTop 5.],
        "text": style [fontFamily "open-sans", fontSize 16., color "white"]
      }
    );

let make ::speakers _children => {
  ...component,
  render: fun _self => {
    let speakerCount = Array.length speakers;
    speakerCount > 1 ?
      <View>
        (
          Array.map
            (
              fun speaker =>
                <View style=styles##wrapper key=speaker##name>
                  <Text value=speaker##name style=styles##heading />
                  <Text style=styles##text value=speaker##bio />
                </View>
            )
            speakers |> ReasonReact.arrayToElement
        )
      </View> :
      <View style=styles##wrapper>
        <Text value="Speaker Bio" style=styles##heading />
        <Text style=styles##text value=speakers.(0)##bio />
      </View>
  }
};
