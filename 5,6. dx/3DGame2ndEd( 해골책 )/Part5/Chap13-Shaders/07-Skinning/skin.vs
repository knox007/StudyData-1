//
// Generated by Microsoft (R) D3DX9 Shader Compiler
//
//  Source: skin.fx
//  Flags: /E:main /T:vs_2_0 
//

// Parameters:
//
//     float4x4 matPal[50];
//     float4x4 matP;
//     float4x4 matV;
//     float3 vLight;
//
//
// Registers:
//
//     Name         Reg   Size
//     ------------ ----- ----
//     matPal       c0     200
//     matP         c200     4
//     matV         c204     3
//     vLight       c207     1
//

    vs_2_0
    def c208, 4, 0, 0, 1
    dcl_position v0
    dcl_normal v1
    dcl_texcoord v2
    dcl_texcoord1 v3
    dcl_texcoord2 v4
    frc r0, v4
    add r2, -r0, v4
    mul r9, r2, c208.x
    mova a0, r9
    mov r4.xyz, v0
    mov r4.w, c208.w
    m4x3 r11.xyz, r4, c0[a0.x]
    mul r6.xyz, r11, v3.x
    m4x3 r1.xyz, r4, c0[a0.y]
    mad r3.xyz, r1, v3.y, r6
    m4x3 r10.xyz, r4, c0[a0.z]
    mad r0.xyz, r10, v3.z, r3
    m4x3 r7.xyz, r4, c0[a0.w]
    mad r9.xyz, r7, v3.w, r0
    mov r9.w, c208.w
    m4x3 r4.xyz, r9, c204
    mov r4.w, c208.w
    m4x4 oPos, r4, c200
    m3x3 r11.xyz, v1, c204
    nrm r6.xyz, r11
    dp3 r1.w, r6, c207
    max oD0, r1.w, c208.y
    mov oT0.xy, v2

// approximately 40 instruction slots used


// 0000:  fffe0200  0033fffe  42415443  00000014  _.....3_CTAB.___
// 0010:  000000b0  fffe0200  00000004  00000014  .____....___.___
// 0020:  00000064  00c80002  00000004  0000006c  d___._._.___l___
// 0030:  00000000  0000007c  00000002  000000c8  ____|___.___.___
// 0040:  00000084  00000000  00000094  00cc0002  ._______.___._._
// 0050:  00000003  0000006c  00000000  00000099  .___l_______.___
// 0060:  00cf0002  00000001  000000a0  00000000  ._._.___._______
// 0070:  5074616d  ababab00  00030003  00040004  matP_...._._._._
// 0080:  00000001  00000000  5074616d  ab006c61  ._______matPal_.
// 0090:  00030003  00040004  00000032  00000000  ._._._._2_______
// 00a0:  5674616d  694c7600  00746867  00030001  matV_vLight_._._
// 00b0:  00030001  00000001  00000000  58443344  ._._._______D3DX
// 00c0:  68532039  72656461  6d6f4320  656c6970  9 Shader Compile
// 00d0:  abab0072  05000051  a00f00d0  40800000  r_..Q__.._..__.@
// 00e0:  00000000  00000000  3f800000  0200001f  __________.?.__.
// 00f0:  80000000  900f0000  0200001f  80000003  ___.__...__..__.
// 0100:  900f0001  0200001f  80000005  900f0002  ._...__..__.._..
// 0110:  0200001f  80010005  900f0003  0200001f  .__.._..._...__.
// 0120:  80020005  900f0004  02000013  800f0000  ._..._...__.__..
// 0130:  90e40004  03000002  800f0002  81e40000  ._...__.._..__..
// 0140:  90e40004  03000005  800f0009  80e40002  ._...__.._..._..
// 0150:  a00000d0  0200002e  b00f0000  80e40009  .__..__.__..._..
// 0160:  02000001  80070004  90e40000  02000001  .__.._..__...__.
// 0170:  80080004  a0ff00d0  04000015  8007000b  ._..._...__.._..
// 0180:  80e40004  a0e42000  b0000000  03000005  ._.._ ..___..__.
// 0190:  80070006  80e4000b  90000003  04000015  ._..._...__..__.
// 01a0:  80070001  80e40004  a0e42000  b0550000  ._..._.._ ..__U.
// 01b0:  04000004  80070003  80e40001  90550003  .__.._..._..._U.
// 01c0:  80e40006  04000015  8007000a  80e40004  ._...__.._..._..
// 01d0:  a0e42000  b0aa0000  04000004  80070000  _ ..__...__.__..
// 01e0:  80e4000a  90aa0003  80e40003  04000015  ._..._..._...__.
// 01f0:  80070007  80e40004  a0e42000  b0ff0000  ._..._.._ ..__..
// 0200:  04000004  80070009  80e40007  90ff0003  .__.._..._..._..
// 0210:  80e40000  02000001  80080009  a0ff00d0  __...__.._..._..
// 0220:  03000015  80070004  80e40009  a0e400cc  .__.._..._..._..
// 0230:  02000001  80080004  a0ff00d0  03000014  .__.._..._...__.
// 0240:  c00f0000  80e40004  a0e400c8  03000017  __..._..._...__.
// 0250:  8007000b  90e40001  a0e400cc  02000024  ._..._..._..$__.
// 0260:  80070006  80e4000b  03000008  80080001  ._..._...__.._..
// 0270:  80e40006  a0e400cf  0300000b  d00f0000  ._..._...__.__..
// 0280:  80ff0001  a05500d0  02000001  e0030000  ._..._U..__.__..
// 0290:  90e40002  0000ffff                      ._....__
