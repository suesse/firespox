function onSpeechRateSyncFromPrefs()
{
    var speechRatePref = document.getElementByID('firespox-speech-rate');
    return speechRatePref.value;
}