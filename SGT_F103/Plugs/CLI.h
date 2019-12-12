/*
 * 提供一个控制台接口，可以提供更加轻松的调试体验或者作为应用的一部分加入到你的产品
 * 
 * 控制台指令的格式：[首字母为>作为CMD命令]
 * >help openLED
 * >openLED 
 * >setMontorSpeed 200
 * >sendMessage helloSGT
 * >openSerial 9600 USART1 8  [暂不支持重载]
 * >openSerial 9600 USART1    [暂不支持重载]
 * 错误格式提醒：
 *  ERROR Undefine Command
 *  ERROR Unfitable Function Params
 *  ERROR Disable translate (hello)X to (int)Type
 *  ERROR Too Few Params
 *  ERROR Too Much Params
 * 
 */

#include <stdbool.h>
