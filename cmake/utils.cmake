# Converts a version such as 1.2.255 to 0x0102ff
# from https://github.com/nghttp2/nghttp2/blob/master/cmake/Version.cmake
function(make_hex_version version_hex_var major minor patch)
  math(EXPR version_dec "${major} * 256 * 256 + ${minor} * 256 + ${patch}")
  set(version_hex "0x")
  foreach(i RANGE 5 0 -1)
    math(EXPR num "(${version_dec} >> (4 * ${i})) & 15")
    string(SUBSTRING "0123456789abcdef" ${num} 1 num_hex)
    set(version_hex "${version_hex}${num_hex}")
  endforeach()
  set(${version_hex_var} "${version_hex}" PARENT_SCOPE)
endfunction()
