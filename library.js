mergeInto(LibraryManager.library, 
{
  js_present_frame: function(ptr, width, height) 
  {
    console.log("js_present_frame called");
    if (!window.ctx) 
    {
      const canvas = document.getElementById("canvas");
      window.ctx = canvas.getContext("2d");
      window.imageData = ctx.createImageData(width, height);
    }

    const imageData = window.imageData;
    const data = imageData.data;
    const buffer = HEAPU32.subarray(ptr >> 2, (ptr >> 2) + width * height);

    for (let i = 0; i < buffer.length; i++)
    {
      const val = buffer[i];
      const j = i * 4;
      data[j] = (val >> 16) & 0xFF;
      data[j + 1] = (val >> 8) & 0xFF;
      data[j + 2] = val & 0xFF;
      data[j + 3] = 255;
    }

    ctx.putImageData(imageData, 0, 0);
  }
});