namespace AIMP.SDK
{
    public class AimpResult<TResult>
    {
        public AimpResult(AimpActionResult actionResult, TResult result)
        {
            ActionResult = actionResult;
            Result = result;
        }

        public AimpActionResult ActionResult { get; set; }

        public TResult Result { get; set; }
    }
}