open ReactNative;

type _state = {scrollRef: option ReasonReact.reactRef};

let setRef theRef _ => ReasonReact.SilentUpdate {scrollRef: Js.Null.to_opt theRef};

let styles =
  StyleSheet.create
    Style.(
      {
        "item": style [flex 1.],
        "row": style [flexDirection `row],
        "titleWrap": style [flex 1., padding 10.],
        "wrapper":
          style [
            position `relative,
            flex 1.,
            backgroundColor "rgb(75, 118, 134)",
            borderWidth 1.,
            borderColor "rgb(137, 167, 177)"
          ]
      }
    );

let component = ReasonReact.statefulComponent "ItemModal";

let make
    item::(item: Item.t)
    ::contentOpacity
    ::backgroundOpacity
    ::expanded
    onClose::(onClose: unit => unit)
    _children => {
  ...component,
  initialState: fun () => {scrollRef: None},
  render: fun self => {
    let fadingContainerStyle value => Style.(style [opacityAnimated value]);
    let contentContainerOpacity = fadingContainerStyle contentOpacity;
    <Animated.View style=Style.(concat [styles##wrapper, fadingContainerStyle backgroundOpacity])>
      <ScrollView style=styles##item ref=(self.update setRef)>
        <View style=styles##row>
          <View style=styles##titleWrap>
            (
              switch (Js.Null_undefined.to_opt item##talk) {
              | None => <ScheduleTitle title=item##title />
              | Some talk => <ScheduleTitle title=talk##title />
              }
            )
            (
              switch (Js.Null_undefined.to_opt item##talk) {
              | None => ReasonReact.nullElement
              | Some t => <SpeakerNames talk=t />
              }
            )
          </View>
          (
            switch (Js.Null_undefined.to_opt item##talk) {
            | None => ReasonReact.nullElement
            | Some t => <SpeakerImages talk=t />
            }
          )
        </View>
        <ScheduleTime start=item##start />
        (
          switch expanded {
          | false => ReasonReact.nullElement
          | true =>
            switch (Js.Null_undefined.to_opt item##talk) {
            | None => ReasonReact.nullElement
            | Some t =>
              <Animated.View style=contentContainerOpacity>
                <TalkDescription value=t##description />
                <SpeakerBio speakers=t##speakers />
              </Animated.View>
            }
          }
        )
      </ScrollView>
      (
        switch expanded {
        | false => ReasonReact.nullElement
        | true =>
          <Animated.View style=contentContainerOpacity>
            <CloseButton
              onPress=(
                fun () => {
                  switch self.state.scrollRef {
                  | None => ()
                  | Some s =>
                    (ReasonReact.refToJsObj s)##scrollTo [%bs.raw "{y: 0, animated: false}"]
                  };
                  onClose ()
                }
              )
            />
          </Animated.View>
        }
      )
    </Animated.View>
  }
};