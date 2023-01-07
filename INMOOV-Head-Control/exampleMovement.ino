bool exampleMovement()
{
  /*
    The lower is a local variable to keep track of the interupt statte that
    is retuned from the rotateToTarget
  */
  bool wasInterrupted = false;
  /*
    The lower method takes an absolute angle to position the pan and tilt of
    the eyes
  */
  head.setEyeRotationTarget(random(15, 45), random(15, 45));
  /*
    The lower variable equals the return of the rotateToTarget method.
    By setting it equal to, it also calls the method. The rotateToTarget
    method moves the servos to the positions entered in the setTarget methods
    and retuns if an interupt was triggered. This line must be included after
    every setTarget method
  */
  wasInterrupted = head.rotateToTarget(duration, &interrupt1, true);
  /*
    The lower method moves the servos to the positions entered in the setTarget
    methods and retuns if ainterupt was trigered
  */
  head.setJawRotationTarget(random(15, 45));
  /*
    The lower variable equals the return of the rotateToTarget method.
    By setting it equal to, it also calls the method. The rotateToTarget
    method moves the servos to the positions entered in the setTarget methods
    and retuns if an interupt was triggered. This line must be included after
    every setTarget method.
  */
  wasInterrupted = head.rotateToTarget(duration, &interrupt1, true);
  /*
    The lower method takes absolute angles to position the yaw, pitch and roll
    of the head
  */
  head.setHeadRotationTarget(random(15, 45), 0, 0);
  /*
    The lower variable equals the return of the rotateToTarget method.
    By setting it equal to, it also calls the method. The rotateToTarget
    method moves the servos to the positions entered in the setTarget methods
    and retuns if an interupt was triggered. This line must be included after
    every setTarget method.
  */
  wasInterrupted = head.rotateToTarget(duration, &interrupt1, true);
  /*
    The lower is what the function returns when it is called, it stores the
    interupt state
  */
  return wasInterrupted;
}
