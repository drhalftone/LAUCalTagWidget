#version 330 core

uniform sampler2D qt_texture;              // THIS TEXTURE HOLDS THE XYZ+TEXTURE COORDINATES
uniform     float qt_maxPixelValue = 1.0;  // USE THIS TO HOLD THE MAXIMUM PIXEL VALUE FOR RESCALING
in           vec2 qt_coordinate;           // HOLDS THE TEXTURE COORDINATE FROM THE VERTEX SHADER

layout(location = 0, index = 0) out vec4 qt_fragColor;

void main()
{
    // GET THE PIXEL COORDINATE OF THE CURRENT FRAGMENT
    qt_fragColor = vec4(texture(qt_texture, qt_coordinate, 0).rgb * qt_maxPixelValue, 1.0);
}
