#ifndef QUIET_VS_CODE_H
#define QUIET_VS_CODE_H

#ifndef QUIET_VSCODE
// Tell VS Code to not put error squiggles under certain C23 features.

#define constexpr const // `constexpr` is defined in C23
#define true 1          // `true` and
#define false 0         // `false` are defined in C23

#endif // QUIET_VSCODE

#endif // QUIET_VS_CODE_H