open ReactNative;

/* Types */
type sourceItemDimensions = {
  x: float,
  y: float,
  width: float,
  height: float
};

type modalAnimationState = {
  top: Animated.Value.t,
  left: Animated.Value.t,
  width: Animated.Value.t,
  height: Animated.Value.t,
  contentOpacity: Animated.Value.t,
  backgroundOpacity: Animated.Value.t
};

type modalState =
  | Collapsing Item.t sourceItemDimensions modalAnimationState
  | Expanding Item.t sourceItemDimensions modalAnimationState
  | Expanded Item.t sourceItemDimensions modalAnimationState
  | Closed;

type _state = {
  modalState,
  selectedIndex: int,
  listOpacity: Animated.Value.t,
  mutable listRef: option ReasonReact.reactRef
};

/* Variables */
let animationDuration = 300.;

let statusOffset =
  PlatformRe.os === PlatformRe.IOS ? 0. : float_of_int StatBar.constants##currentHeight;

let listPadding = 10;

let iosBarHeight = 20.;

let deferDuration = 0;

let windowWidth = (Dimensions.get `window)##width;

let easeIn x => x *. x *. x;

/* Methods */
let closeModal _ {ReasonReact.state: state} => ReasonReact.Update {...state, modalState: Closed};

let setRef theRef {ReasonReact.state: state} => state.listRef = Js.Null.to_opt theRef;

let startExpandingModal (x, y, width, height, item, selectedIndex) {ReasonReact.state: state} =>
  switch state.modalState {
  | Closed =>
    /* Handle target dimensions */
    let fx = float_of_int x;
    let fy = float_of_int y;
    let fw = float_of_int width;
    let fh = float_of_int height;
    let targetDimensions = {x: fx, y: fy +. statusOffset, width: fw, height: fh};
    let newAnimatedValue x => Animated.Value.create x;
    ReasonReact.Update {
      ...state,
      modalState:
        Expanding
          item
          targetDimensions
          {
            top: newAnimatedValue (fy +. statusOffset),
            left: newAnimatedValue fx,
            width: newAnimatedValue fw,
            height: newAnimatedValue fh,
            contentOpacity: newAnimatedValue 0.,
            backgroundOpacity: newAnimatedValue 1.
          },
      selectedIndex
    }
  | _ => ReasonReact.NoUpdate
  };

let startCollapsingModal _ {ReasonReact.state: state} =>
  switch state.modalState {
  | Expanded item sourceItemDimensions modalState =>
    ReasonReact.Update {...state, modalState: Collapsing item sourceItemDimensions modalState}
  | _ => failwith "TODO: this is impossible state"
  };

/* Component */
let component = ReasonReact.statefulComponent "Schedule";

/* Styles */
let styles =
  StyleSheet.create
    Style.(
      {
        "container":
          style [
            flex 1.,
            alignItems `stretch,
            justifyContent `center,
            backgroundColor "rgb(54, 97, 115)",
            paddingTop (
              PlatformRe.os === PlatformRe.IOS ?
                20. : float_of_int StatBar.constants##currentHeight
            )
          ],
        "scrollView": style [flex 1.],
        "contentContainer":
          style [paddingBottom 10., flexGrow 1., width (float_of_int windowWidth)],
        "modal": style [position `absolute, bottom 5., right 5., width 25., height 25.],
        "date":
          style [
            fontFamily "open-sans-bold",
            letterSpacing 1.,
            color "rgb(185,219,111)",
            backgroundColor "rgb(54, 97, 115)",
            textAlign `center,
            fontSize 18.,
            padding 10.
          ],
        "dateWrap": style [borderBottomWidth 1., borderBottomColor "rgba(255,255,255,0.75)"],
        "banner":
          style [
            width (float_of_int windowWidth),
            height (float_of_int windowWidth *. 0.656),
            marginBottom 0.
          ]
      }
    );

let onExpandAnimationFinish
    (item, sourceItemDimensions, modalAnimationState)
    {ReasonReact.state: state} =>
  ReasonReact.Update {
    ...state,
    modalState: Expanded item sourceItemDimensions modalAnimationState
  };

let onCollapseAnimationFinish _ {ReasonReact.state: state} =>
  ReasonReact.Update {...state, modalState: Closed};

let animateExpandModal
    ::listRef
    ::listOpacity
    ::modalAnimationState
    ::item
    ::sourceItemDimensions
    ::onFinish => {
  let {top, width, height, contentOpacity} = modalAnimationState;
  let windowWidth = (DimensionsRe.get `window)##width - listPadding * 2;
  switch listRef {
  | None => ()
  | Some r =>
    (ReasonReact.refToJsObj r)##measure (
      fun _x _y _width _height => {
        let wh = _height - listPadding * 2;
        /* Define animations */
        let animationBatch =
          Animated.parallel
            [|
              Animated.Timing.animate
                value::listOpacity
                toValue::(`raw 0.)
                easing::easeIn
                duration::animationDuration
                (),
              Animated.Timing.animate
                value::top
                toValue::(
                  `raw (
                    PlatformRe.os === PlatformRe.IOS ?
                      iosBarHeight +. float_of_int listPadding :
                      statusOffset +. float_of_int listPadding
                  )
                )
                easing::easeIn
                duration::animationDuration
                (),
              Animated.Timing.animate
                value::width
                toValue::(`raw (float_of_int windowWidth))
                easing::easeIn
                duration::animationDuration
                (),
              Animated.Timing.animate
                value::height
                toValue::(`raw (float_of_int wh))
                easing::easeIn
                duration::animationDuration
                ()
            |]
            [%bs.raw "{stopTogether: true}"];
        /* Start animations */
        Animated.CompositeAnimation.start
          animationBatch
          callback::(
            fun _ => {
              let _id =
                Js.Global.setTimeout
                  (
                    fun _ => {
                      onFinish (item, sourceItemDimensions, modalAnimationState);
                      let _id =
                        Js.Global.setTimeout
                          (
                            fun _ => {
                              let animation =
                                Animated.Timing.animate
                                  value::contentOpacity
                                  toValue::(`raw 1.)
                                  easing::easeIn
                                  duration::animationDuration
                                  ();
                              Animated.CompositeAnimation.start animation ()
                            }
                          )
                          deferDuration;
                      ()
                    }
                  )
                  deferDuration;
              ()
            }
          )
          ()
      }
    )
  }
};

let animateCollapseModal
    ::listOpacity
    sourceItemDimensions::{width: sourceWidth, y: sourceY, height: sourceHeight}
    modalAnimationState::{top, width, height, contentOpacity, backgroundOpacity}
    ::onFinish => {
  let animationBatch =
    Animated.parallel
      [|
        Animated.Timing.animate
          value::listOpacity toValue::(`raw 1.) easing::easeIn duration::animationDuration (),
        Animated.Timing.animate
          value::contentOpacity toValue::(`raw 0.) easing::easeIn duration::animationDuration (),
        Animated.Timing.animate
          delay::(animationDuration *. 0.8)
          value::backgroundOpacity
          toValue::(`raw 0.)
          easing::easeIn
          duration::(animationDuration *. 0.2)
          (),
        Animated.Timing.animate
          value::top toValue::(`raw sourceY) easing::easeIn duration::animationDuration (),
        Animated.Timing.animate
          value::width toValue::(`raw sourceWidth) easing::easeIn duration::animationDuration (),
        Animated.Timing.animate
          value::height toValue::(`raw sourceHeight) easing::easeIn duration::animationDuration ()
      |]
      {"stopTogether": Js.true_};
  /* Start animations */
  Animated.CompositeAnimation.start
    animationBatch
    callback::(
      fun _finished => {
        let _ =
          Js.Global.setTimeout
            (
              fun () => {
                onFinish ();
                Animated.CompositeAnimation.start
                  (
                    Animated.Timing.animate
                      value::listOpacity
                      toValue::(`raw 1.)
                      easing::easeIn
                      duration::animationDuration
                      ()
                  )
                  ()
              }
            )
            deferDuration;
        ()
      }
    )
    ()
};

/* Make */
let make data::(data: Item.data) _children => {
  let loading = Js.to_bool data##loading;
  let error = data##error;
  let schedule =
    (
      switch (Js.Null_undefined.to_opt data##allSchedules) {
      | None => []
      | Some arr => Array.to_list arr
      }
    ) |>
    List.map Item.convert_from_js;
  {
    ...component,
    initialState: fun () => {
      listOpacity: Animated.Value.create 1.,
      modalState: Closed,
      selectedIndex: 0,
      listRef: None
    },
    didUpdate:
      fun {
            oldSelf: {state: {modalState: oldModalState}},
            newSelf: {state: {modalState: newModalState, listRef, listOpacity}, update}
          } =>
      switch (oldModalState, newModalState) {
      | (Closed, Expanding item sourceItemDimensions modalAnimationState) =>
        animateExpandModal
          ::listRef
          ::listOpacity
          ::modalAnimationState
          ::item
          ::sourceItemDimensions
          onFinish::(update onExpandAnimationFinish)
      | (Expanded _ _ _, Collapsing _ sourceItemDimensions modalAnimationState) =>
        animateCollapseModal
          ::listOpacity
          ::sourceItemDimensions
          ::modalAnimationState
          onFinish::(update onCollapseAnimationFinish)
      | (_, _) => ()
      },
    render: fun self =>
      <View style=styles##container>
        <StatusBar backgroundColor="#ffffff" barStyle=`lightContent />
        <Animated.View style=Style.(style [opacityAnimated self.state.listOpacity, flex 1.])>
          <View ref=(self.handle setRef) style=styles##scrollView collapsable=false>
            <ScrollView
              scrollEnabled=(
                switch self.state.modalState {
                | Closed => true
                | _ => false
                }
              )
              style=styles##scrollView
              stickyHeaderIndices=(
                loading == false ? [1, Utils.getIndexFromSchedule schedule] : []
              )
              contentContainerStyle=styles##contentContainer>
              <Image
                source=Image.(Required (Packager.require "../../../static/banner.png"))
                style=styles##banner
                resizeMode=`cover
              />
              (
                loading == true ?
                  <View style=Style.(style [flex 1., alignItems `center, justifyContent `center])>
                    <ActivityIndicator />
                  </View> :
                  (
                    switch (Js.Null_undefined.to_opt error) {
                    | None =>
                      Utils.getUniqueDates schedule |>
                      List.map (
                        fun date =>
                          List.concat [
                            [
                              <View key=date style=styles##dateWrap>
                                <Text
                                  style=styles##date
                                  value=(
                                    String.uppercase
                                      Moment.(moment date |> Moment.format "dddd, MMMM Do")
                                  )
                                />
                              </View>
                            ],
                            List.mapi
                              (
                                fun index (item: Item.t) =>
                                  switch item.talk {
                                  | None => <ScheduleItem item key=item.id />
                                  | Some talk =>
                                    <TalkItem
                                      item
                                      talk
                                      index
                                      selectedIndex=self.state.selectedIndex
                                      modalOpen=(
                                        switch self.state.modalState {
                                        | Expanded _ _ _ => true
                                        | _ => false
                                        }
                                      )
                                      key=item.id
                                      onPress=(self.update startExpandingModal)
                                    />
                                  }
                              )
                              (Utils.getScheduleForDate schedule date)
                          ]
                      ) |> List.concat |> Array.of_list |> ReasonReact.arrayToElement
                    | Some e =>
                      <View
                        style=Style.(style [flex 1., alignItems `center, justifyContent `center])>
                        <Text value=e##message />
                      </View>
                    }
                  )
              )
            </ScrollView>
          </View>
        </Animated.View>
        /* </LinearGradient> */
        (
          switch self.state.modalState {
          | Closed => ReasonReact.nullElement
          /* The fields from the modalAnimationState record
                are bound to names with trailing apostrophes
                because top, left, height, and width were
                shadowed by values from Style module
             */
          | Collapsing item _ modalAnimationState
          | Expanding item _ modalAnimationState
          | Expanded item _ modalAnimationState =>
            let {
              top: top',
              left: left',
              height: height',
              width: width',
              contentOpacity,
              backgroundOpacity
            } = modalAnimationState;
            <Animated.View
              style=Style.(
                      concat [
                        styles##modal,
                        style [
                          position `absolute,
                          topAnimated top',
                          leftAnimated left',
                          widthAnimated width',
                          heightAnimated height',
                          overflow `hidden
                        ]
                      ]
                    )>
              <ItemModal
                contentOpacity
                backgroundOpacity
                item
                expanded=(
                  switch self.state.modalState {
                  | Expanded _ _ _ => true
                  | _ => false
                  }
                )
                onClose=(self.update startCollapsingModal)
              />
            </Animated.View>
          }
        )
      </View>
  }
};

let wrappedComponent = {
  module M = ReactApollo.CreateWrapper Item;
  M.wrapComponent ::component ::make
};