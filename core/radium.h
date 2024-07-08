#ifndef CORE_RADIUM_H_
#define CORE_RADIUM_H_

namespace radium
{

constexpr char versionStr[] = "0.0.1";


} // radium

#define EDITOR_VARIABLE(type, name) \
private: \
type name;\
public:\
type get##name() { return name; }

#endif // CORE_RADIUM_H_