Bug(s):
- Waits for the backend to complete before displaying its output. Might be related to threads or the inputstream methods.
- Sliders will sometimes limit their corresponding text fields, this is because the text fields update when anything is changed in them, not when the user presses Enter
