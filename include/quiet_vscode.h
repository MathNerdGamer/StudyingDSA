#ifndef QUIET_VS_CODE_H
#define QUIET_VS_CODE_H

#ifndef QUIET_VSCODE
// Tell VS Code to not put error squiggles under certain C23 features.

#ifdef __cplusplus
// Sometimes VS Code doesn't realize a header is supposed to be C code,
// so it complains when I use stuff that would be in namespace std (like
// `std::size_t`).
using namespace std;
#else

#define constexpr const // `constexpr` is defined in C23.
#define true 1          // `true` and
#define false 0         // `false` are defined in C23.
#define nullptr NULL    // `nullptr` is also defined in C23.

#endif // __cplusplus

#endif // QUIET_VSCODE

#endif // QUIET_VS_CODE_H