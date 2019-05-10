#version 330 core

uniform sampler2D qt_texture;      // THIS TEXTURE HOLDS THE XYZ+TEXTURE COORDINATES
in           vec2 qt_coordinate;   // HOLDS THE TEXTURE COORDINATE FROM THE VERTEX SHADER

layout(location = 0, index = 0) out vec4 qt_fragColor;

void main()
{
    // CONVERT THE TEXTURE COORDINATE TO PIXEL COORDINATE
    ivec2 size = textureSize(qt_texture, 0);
    ivec2 coord = ivec2(round(vec2(size-ivec2(1, 1)) * qt_coordinate));

    // GET THE PIXEL COORDINATE OF THE CURRENT FRAGMENT
    qt_fragColor = vec4(texelFetch(qt_texture, coord, 0).bbb, 1.0);

    return;
}
