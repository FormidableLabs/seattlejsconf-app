open ReactNative;

let component = ReasonReact.statelessComponent "SpeakerImages";

let styles =
  StyleSheet.create
    Style.(
      {
        "speakerWrapper":
          style [
            flex 0.,
            flexDirection `row,
            justifyContent `center,
            alignItems `center,
            padding 10.
          ],
        "speakerImage":
          style [
            height 75.,
            width 75.,
            borderRadius 37.5,
            borderWidth 4.,
            borderColor "rgba(255,255,255,0.5)"
          ]
      }
    );

let make talk::{Item.speakers: speakers} _children => {
  ...component,
  render: fun _self =>
    <View style=styles##speakerWrapper>
      {
        let speakerLength = Array.length speakers;
        Array.mapi
          (
            fun i {Item.name: name, photo} =>
              <Image
                key=name
                source=(
                  URI Image.(
                        imageURISource
                          uri::(
                            "https://images.graph.cool/v1/cj5cm0t4pnljk01087tv4g61a/" ^
                            photo ^ "/150x150"
                          )
                          ()
                      )
                )
                style=Style.(
                        concat [
                          styles##speakerImage,
                          style [speakerLength > 1 && i === 0 ? left 25. : opacity 1.]
                        ]
                      )
              />
          )
          speakers |> ReasonReact.arrayToElement
      }
    </View>
};