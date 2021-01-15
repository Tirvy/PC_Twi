
// This is our task - a global or static function that has to return DoneStatus.
// The task object is passed as argument, plus a void* pointer, containing custom data.
// For more advanced usage, we can subclass AsyncTask and override the do_task method.
AsyncTask::DoneStatus spinCameraTask(GenericAsyncTask* task, void* data) {
  // Calculate the new position and orientation (inefficient - change me!)

	//_Camera.set_pos(0.0,	96.0,	96.0);
	//_Camera.set_hpr(160.0,	-53.0,	0.0);
 
  // Tell the task manager to continue this task the next frame.
  return AsyncTask::DS_cont;
}