mergeInto(LibraryManager.library, 
{
  js_presentframe: function(ptr, width, height) 
  {
    if (!window.ctx) 
    {
      const canvas = document.getElementById("canvas");
      window.ctx = canvas.getContext("2d");
      window.imageData = ctx.createImageData(width, height);
      ctx.imageSmoothingEnabled = false;
      ctx.webkitImageSmoothingEnabled = false;
      ctx.mozImageSmoothingEnabled = false;
      ctx.msImageSmoothingEnabled = false;
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
  },

  js_setupinput: function()
  {
    console.log('setup');
    document.addEventListener('keydown', function (e) {
      if (Module._i_keydown)
          Module._i_keydown(e.keyCode);
    });
    
    document.addEventListener('keyup', function (e) {
      if (Module._i_keyup)
          Module._i_keyup(e.keyCode);
    });
  }
});