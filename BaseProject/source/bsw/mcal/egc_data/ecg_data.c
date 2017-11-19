#include "ecg_data.h"

float ecg_resampled[2048] = {
-0.1451, 
-0.1649, 
-0.1577, 
-0.1419, 
-0.1347, 
-0.1399, 
-0.1486, 
-0.1514, 
-0.1471, 
-0.1418, 
-0.1410, 
-0.1446, 
-0.1479, 
-0.1477, 
-0.1447, 
-0.1424, 
-0.1432, 
-0.1460, 
-0.1473, 
-0.1442, 
-0.1367, 
-0.1277, 
-0.1217, 
-0.1216, 
-0.1271, 
-0.1351, 
-0.1413, 
-0.1440, 
-0.1443, 
-0.1444, 
-0.1469, 
-0.1514, 
-0.1560, 
-0.1591, 
-0.1593, 
-0.1574, 
-0.1554, 
-0.1546, 
-0.1564, 
-0.1604, 
-0.1654, 
-0.1705, 
-0.1747, 
-0.1776, 
-0.1799, 
-0.1818, 
-0.1832, 
-0.1841, 
-0.1825, 
-0.1777, 
-0.1701, 
-0.1617, 
-0.1565, 
-0.1567, 
-0.1616, 
-0.1685, 
-0.1744, 
-0.1778, 
-0.1803, 
-0.1831, 
-0.1866, 
-0.1896, 
-0.1894, 
-0.1858, 
-0.1797, 
-0.1717, 
-0.1634, 
-0.1549, 
-0.1462, 
-0.1396, 
-0.1375, 
-0.1424, 
-0.1544, 
-0.1693, 
-0.1822, 
-0.1901, 
-0.1937, 
-0.1979, 
-0.2062, 
-0.2174, 
-0.2274, 
-0.2316, 
-0.2299, 
-0.2274, 
-0.2289, 
-0.2356, 
-0.2445, 
-0.2500, 
-0.2510, 
-0.2498, 
-0.2500, 
-0.2542, 
-0.2615, 
-0.2687, 
-0.2738, 
-0.2759, 
-0.2758, 
-0.2752, 
-0.2748, 
-0.2750, 
-0.2752, 
-0.2736, 
-0.2699, 
-0.2646, 
-0.2592, 
-0.2565, 
-0.2573, 
-0.2606, 
-0.2649, 
-0.2683, 
-0.2713, 
-0.2752, 
-0.2801, 
-0.2856, 
-0.2900, 
-0.2914, 
-0.2909, 
-0.2897, 
-0.2890, 
-0.2896, 
-0.2905, 
-0.2907, 
-0.2901, 
-0.2882, 
-0.2862, 
-0.2852, 
-0.2857, 
-0.2895, 
-0.2959, 
-0.3018, 
-0.3044, 
-0.3016, 
-0.2943, 
-0.2863, 
-0.2801, 
-0.2767, 
-0.2753, 
-0.2740, 
-0.2738, 
-0.2754, 
-0.2774, 
-0.2791, 
-0.2795, 
-0.2802, 
-0.2847, 
-0.2929, 
-0.3010, 
-0.3043, 
-0.3002, 
-0.2933, 
-0.2902, 
-0.2925, 
-0.2976, 
-0.2991, 
-0.2938, 
-0.2861, 
-0.2817, 
-0.2832, 
-0.2891, 
-0.2944, 
-0.2975, 
-0.3003, 
-0.3042, 
-0.3099, 
-0.3150, 
-0.3172, 
-0.3182, 
-0.3207, 
-0.3262, 
-0.3348, 
-0.3437, 
-0.3520, 
-0.3602, 
-0.3689, 
-0.3781, 
-0.3853, 
-0.3882, 
-0.3872, 
-0.3849, 
-0.3862, 
-0.3945, 
-0.4102, 
-0.4315, 
-0.4526, 
-0.4693, 
-0.4801, 
-0.4851, 
-0.4873, 
-0.4881, 
-0.4847, 
-0.4744, 
-0.4532, 
-0.4196, 
-0.3777, 
-0.3331, 
-0.2910, 
-0.2534, 
-0.2174, 
-0.1767, 
-0.1275, 
-0.0700, 
-0.0071, 
0.0562, 
0.1209, 
0.1938, 
0.2814, 
0.3860, 
0.5000, 
0.6070, 
0.6922, 
0.7483, 
0.7802, 
0.8016, 
0.8218, 
0.8400, 
0.8439, 
0.8155, 
0.7467, 
0.6440, 
0.5233, 
0.4015, 
0.2852, 
0.1709, 
0.0554, 
-0.0596, 
-0.1651, 
-0.2507, 
-0.3140, 
-0.3591, 
-0.3918, 
-0.4156, 
-0.4298, 
-0.4320, 
-0.4237, 
-0.4083, 
-0.3895, 
-0.3707, 
-0.3541, 
-0.3402, 
-0.3310, 
-0.3265, 
-0.3251, 
-0.3267, 
-0.3299, 
-0.3343, 
-0.3400, 
-0.3440, 
-0.3445, 
-0.3414, 
-0.3356, 
-0.3302, 
-0.3269, 
-0.3258, 
-0.3253, 
-0.3231, 
-0.3192, 
-0.3144, 
-0.3109, 
-0.3107, 
-0.3128, 
-0.3163, 
-0.3203, 
-0.3239, 
-0.3289, 
-0.3353, 
-0.3401, 
-0.3414, 
-0.3378, 
-0.3314, 
-0.3279, 
-0.3299, 
-0.3365, 
-0.3435, 
-0.3452, 
-0.3413, 
-0.3352, 
-0.3302, 
-0.3291, 
-0.3310, 
-0.3330, 
-0.3343, 
-0.3340, 
-0.3324, 
-0.3304, 
-0.3277, 
-0.3256, 
-0.3253, 
-0.3263, 
-0.3283, 
-0.3301, 
-0.3300, 
-0.3296, 
-0.3307, 
-0.3349, 
-0.3427, 
-0.3509, 
-0.3556, 
-0.3547, 
-0.3482, 
-0.3404, 
-0.3352, 
-0.3321, 
-0.3295, 
-0.3244, 
-0.3163, 
-0.3097, 
-0.3080, 
-0.3118, 
-0.3183, 
-0.3223, 
-0.3222, 
-0.3207, 
-0.3204, 
-0.3241, 
-0.3305, 
-0.3359, 
-0.3388, 
-0.3386, 
-0.3368, 
-0.3358, 
-0.3362, 
-0.3377, 
-0.3401, 
-0.3417, 
-0.3432, 
-0.3452, 
-0.3476, 
-0.3513, 
-0.3552, 
-0.3571, 
-0.3567, 
-0.3531, 
-0.3471, 
-0.3409, 
-0.3355, 
-0.3318, 
-0.3303, 
-0.3295, 
-0.3297, 
-0.3302, 
-0.3298, 
-0.3297, 
-0.3305, 
-0.3331, 
-0.3386, 
-0.3451, 
-0.3495, 
-0.3492, 
-0.3428, 
-0.3332, 
-0.3252, 
-0.3211, 
-0.3222, 
-0.3260, 
-0.3287, 
-0.3296, 
-0.3289, 
-0.3283, 
-0.3299, 
-0.3323, 
-0.3344, 
-0.3352, 
-0.3342, 
-0.3338, 
-0.3354, 
-0.3378, 
-0.3397, 
-0.3389, 
-0.3354, 
-0.3323, 
-0.3316, 
-0.3343, 
-0.3397, 
-0.3445, 
-0.3479, 
-0.3502, 
-0.3516, 
-0.3535, 
-0.3550, 
-0.3545, 
-0.3525, 
-0.3493, 
-0.3461, 
-0.3441, 
-0.3416, 
-0.3372, 
-0.3307, 
-0.3231, 
-0.3191, 
-0.3210, 
-0.3264, 
-0.3318, 
-0.3334, 
-0.3317, 
-0.3313, 
-0.3346, 
-0.3404, 
-0.3440, 
-0.3415, 
-0.3352, 
-0.3302, 
-0.3293, 
-0.3323, 
-0.3352, 
-0.3352, 
-0.3347, 
-0.3360, 
-0.3398, 
-0.3442, 
-0.3458, 
-0.3451, 
-0.3454, 
-0.3479, 
-0.3523, 
-0.3549, 
-0.3521, 
-0.3460, 
-0.3400, 
-0.3371, 
-0.3383, 
-0.3402, 
-0.3396, 
-0.3359, 
-0.3306, 
-0.3278, 
-0.3302, 
-0.3362, 
-0.3439, 
-0.3496, 
-0.3514, 
-0.3509, 
-0.3493, 
-0.3473, 
-0.3451, 
-0.3414, 
-0.3375, 
-0.3353, 
-0.3346, 
-0.3351, 
-0.3351, 
-0.3336, 
-0.3335, 
-0.3364, 
-0.3420, 
-0.3485, 
-0.3528, 
-0.3543, 
-0.3550, 
-0.3556, 
-0.3561, 
-0.3552, 
-0.3515, 
-0.3476, 
-0.3456, 
-0.3454, 
-0.3457, 
-0.3439, 
-0.3399, 
-0.3370, 
-0.3376, 
-0.3425, 
-0.3498, 
-0.3554, 
-0.3586, 
-0.3599, 
-0.3597, 
-0.3599, 
-0.3601, 
-0.3599, 
-0.3604, 
-0.3616, 
-0.3632, 
-0.3647, 
-0.3641, 
-0.3620, 
-0.3602, 
-0.3601, 
-0.3640, 
-0.3711, 
-0.3780, 
-0.3824, 
-0.3821, 
-0.3773, 
-0.3711, 
-0.3653, 
-0.3617, 
-0.3602, 
-0.3585, 
-0.3567, 
-0.3552, 
-0.3545, 
-0.3567, 
-0.3613, 
-0.3671, 
-0.3731, 
-0.3768, 
-0.3773, 
-0.3752, 
-0.3710, 
-0.3672, 
-0.3652, 
-0.3645, 
-0.3649, 
-0.3650, 
-0.3636, 
-0.3618, 
-0.3601, 
-0.3594, 
-0.3603, 
-0.3615, 
-0.3631, 
-0.3652, 
-0.3669, 
-0.3688, 
-0.3700, 
-0.3681, 
-0.3626, 
-0.3533, 
-0.3421, 
-0.3325, 
-0.3265, 
-0.3243, 
-0.3250, 
-0.3254, 
-0.3252, 
-0.3252, 
-0.3262, 
-0.3301, 
-0.3356, 
-0.3399, 
-0.3410, 
-0.3368, 
-0.3277, 
-0.3170, 
-0.3072, 
-0.3014, 
-0.3001, 
-0.3008, 
-0.3013, 
-0.2998, 
-0.2959, 
-0.2924, 
-0.2909, 
-0.2916, 
-0.2937, 
-0.2945, 
-0.2931, 
-0.2905, 
-0.2874, 
-0.2856, 
-0.2852, 
-0.2837, 
-0.2802, 
-0.2743, 
-0.2669, 
-0.2606, 
-0.2563, 
-0.2533, 
-0.2509, 
-0.2484, 
-0.2475, 
-0.2502, 
-0.2555, 
-0.2615, 
-0.2647, 
-0.2633, 
-0.2593, 
-0.2546, 
-0.2501, 
-0.2454, 
-0.2393, 
-0.2334, 
-0.2311, 
-0.2334, 
-0.2393, 
-0.2452, 
-0.2470, 
-0.2460, 
-0.2450, 
-0.2463, 
-0.2508, 
-0.2554, 
-0.2571, 
-0.2549, 
-0.2496, 
-0.2438, 
-0.2407, 
-0.2408, 
-0.2447, 
-0.2504, 
-0.2545, 
-0.2557, 
-0.2534, 
-0.2493, 
-0.2467, 
-0.2472, 
-0.2503, 
-0.2541, 
-0.2554, 
-0.2536, 
-0.2502, 
-0.2471, 
-0.2473, 
-0.2512, 
-0.2565, 
-0.2613, 
-0.2634, 
-0.2626, 
-0.2607, 
-0.2590, 
-0.2587, 
-0.2601, 
-0.2617, 
-0.2634, 
-0.2651, 
-0.2665, 
-0.2684, 
-0.2698, 
-0.2691, 
-0.2662, 
-0.2619, 
-0.2590, 
-0.2604, 
-0.2652, 
-0.2711, 
-0.2752, 
-0.2762, 
-0.2773, 
-0.2807, 
-0.2854, 
-0.2887, 
-0.2873, 
-0.2816, 
-0.2759, 
-0.2727, 
-0.2717, 
-0.2701, 
-0.2656, 
-0.2611, 
-0.2607, 
-0.2655, 
-0.2734, 
-0.2794, 
-0.2812, 
-0.2809, 
-0.2812, 
-0.2829, 
-0.2844, 
-0.2827, 
-0.2787, 
-0.2752, 
-0.2737, 
-0.2746, 
-0.2750, 
-0.2725, 
-0.2685, 
-0.2655, 
-0.2657, 
-0.2699, 
-0.2756, 
-0.2809, 
-0.2850, 
-0.2873, 
-0.2891, 
-0.2900, 
-0.2884, 
-0.2846, 
-0.2794, 
-0.2752, 
-0.2752, 
-0.2789, 
-0.2832, 
-0.2850, 
-0.2826, 
-0.2795, 
-0.2802, 
-0.2854, 
-0.2934, 
-0.2996, 
-0.3012, 
-0.3004, 
-0.3001, 
-0.3016, 
-0.3038, 
-0.3032, 
-0.2997, 
-0.2957, 
-0.2937, 
-0.2958, 
-0.3005, 
-0.3049, 
-0.3079, 
-0.3092, 
-0.3094, 
-0.3095, 
-0.3089, 
-0.3074, 
-0.3051, 
-0.3017, 
-0.2982, 
-0.2952, 
-0.2917, 
-0.2883, 
-0.2852, 
-0.2831, 
-0.2837, 
-0.2864, 
-0.2892, 
-0.2906, 
-0.2903, 
-0.2908, 
-0.2950, 
-0.3019, 
-0.3081, 
-0.3094, 
-0.3040, 
-0.2962, 
-0.2911, 
-0.2907, 
-0.2941, 
-0.2975, 
-0.2991, 
-0.3002, 
-0.3016, 
-0.3036, 
-0.3052, 
-0.3054, 
-0.3067, 
-0.3109, 
-0.3169, 
-0.3219, 
-0.3223, 
-0.3175, 
-0.3110, 
-0.3056, 
-0.3025, 
-0.3001, 
-0.2961, 
-0.2919, 
-0.2906, 
-0.2937, 
-0.3015, 
-0.3109, 
-0.3186, 
-0.3242, 
-0.3274, 
-0.3290, 
-0.3293, 
-0.3268, 
-0.3217, 
-0.3152, 
-0.3081, 
-0.3031, 
-0.3009, 
-0.3009, 
-0.3029, 
-0.3055, 
-0.3078, 
-0.3104, 
-0.3128, 
-0.3159, 
-0.3201, 
-0.3240, 
-0.3276, 
-0.3299, 
-0.3297, 
-0.3278, 
-0.3244, 
-0.3199, 
-0.3159, 
-0.3126, 
-0.3105, 
-0.3099, 
-0.3090, 
-0.3074, 
-0.3052, 
-0.3028, 
-0.3030, 
-0.3059, 
-0.3091, 
-0.3103, 
-0.3077, 
-0.3031, 
-0.3007, 
-0.3016, 
-0.3042, 
-0.3048, 
-0.3006, 
-0.2944, 
-0.2905, 
-0.2910, 
-0.2956, 
-0.3002, 
-0.3017, 
-0.3012, 
-0.3006, 
-0.3017, 
-0.3045, 
-0.3065, 
-0.3068, 
-0.3052, 
-0.3013, 
-0.2960, 
-0.2898, 
-0.2838, 
-0.2811, 
-0.2828, 
-0.2879, 
-0.2944, 
-0.2991, 
-0.3022, 
-0.3052, 
-0.3086, 
-0.3124, 
-0.3149, 
-0.3137, 
-0.3098, 
-0.3043, 
-0.2991, 
-0.2955, 
-0.2931, 
-0.2912, 
-0.2898, 
-0.2875, 
-0.2843, 
-0.2802, 
-0.2753, 
-0.2719, 
-0.2708, 
-0.2715, 
-0.2734, 
-0.2748, 
-0.2750, 
-0.2747, 
-0.2739, 
-0.2726, 
-0.2699, 
-0.2643, 
-0.2570, 
-0.2502, 
-0.2463, 
-0.2474, 
-0.2515, 
-0.2546, 
-0.2532, 
-0.2458, 
-0.2352, 
-0.2262, 
-0.2212, 
-0.2202, 
-0.2201, 
-0.2171, 
-0.2113, 
-0.2048, 
-0.2003, 
-0.1998, 
-0.2018, 
-0.2042, 
-0.2058, 
-0.2068, 
-0.2094, 
-0.2149, 
-0.2217, 
-0.2275, 
-0.2295, 
-0.2271, 
-0.2231, 
-0.2206, 
-0.2210, 
-0.2238, 
-0.2261, 
-0.2265, 
-0.2254, 
-0.2239, 
-0.2237, 
-0.2252, 
-0.2267, 
-0.2284, 
-0.2300, 
-0.2313, 
-0.2331, 
-0.2352, 
-0.2373, 
-0.2391, 
-0.2396, 
-0.2382, 
-0.2350, 
-0.2300, 
-0.2247, 
-0.2202, 
-0.2161, 
-0.2130, 
-0.2103, 
-0.2082, 
-0.2091, 
-0.2148, 
-0.2266, 
-0.2439, 
-0.2622, 
-0.2770, 
-0.2852, 
-0.2863, 
-0.2850, 
-0.2855, 
-0.2888, 
-0.2946, 
-0.3002, 
-0.3049, 
-0.3103, 
-0.3168, 
-0.3240, 
-0.3298, 
-0.3317, 
-0.3312, 
-0.3300, 
-0.3288, 
-0.3274, 
-0.3245, 
-0.3199, 
-0.3165, 
-0.3158, 
-0.3174, 
-0.3196, 
-0.3193, 
-0.3170, 
-0.3152, 
-0.3156, 
-0.3196, 
-0.3258, 
-0.3314, 
-0.3359, 
-0.3392, 
-0.3416, 
-0.3440, 
-0.3449, 
-0.3435, 
-0.3406, 
-0.3373, 
-0.3371, 
-0.3407, 
-0.3454, 
-0.3487, 
-0.3485, 
-0.3461, 
-0.3457, 
-0.3485, 
-0.3527, 
-0.3539, 
-0.3484, 
-0.3386, 
-0.3302, 
-0.3271, 
-0.3304, 
-0.3358, 
-0.3375, 
-0.3343, 
-0.3277, 
-0.3222, 
-0.3218, 
-0.3265, 
-0.3350, 
-0.3446, 
-0.3515, 
-0.3548, 
-0.3546, 
-0.3506, 
-0.3454, 
-0.3399, 
-0.3344, 
-0.3306, 
-0.3279, 
-0.3260, 
-0.3255, 
-0.3253, 
-0.3265, 
-0.3302, 
-0.3354, 
-0.3426, 
-0.3503, 
-0.3565, 
-0.3612, 
-0.3636, 
-0.3635, 
-0.3626, 
-0.3629, 
-0.3683, 
-0.3802, 
-0.3965, 
-0.4128, 
-0.4246, 
-0.4318, 
-0.4378, 
-0.4465, 
-0.4598, 
-0.4745, 
-0.4876, 
-0.4991, 
-0.5098, 
-0.5213, 
-0.5315, 
-0.5354, 
-0.5316, 
-0.5205, 
-0.5034, 
-0.4815, 
-0.4508, 
-0.4085, 
-0.3573, 
-0.3026, 
-0.2505, 
-0.2037, 
-0.1596, 
-0.1149, 
-0.0675, 
-0.0139, 
0.0526, 
0.1384, 
0.2451, 
0.3642, 
0.4787, 
0.5763, 
0.6542, 
0.7186, 
0.7780, 
0.8320, 
0.8756, 
0.9068, 
0.9262, 
0.9381, 
0.9418, 
0.9286, 
0.8913, 
0.8304, 
0.7535, 
0.6706, 
0.5840, 
0.4895, 
0.3851, 
0.2742, 
0.1655, 
0.0667, 
-0.0228, 
-0.1071, 
-0.1871, 
-0.2597, 
-0.3186, 
-0.3605, 
-0.3894, 
-0.4118, 
-0.4318, 
-0.4503, 
-0.4648, 
-0.4721, 
-0.4734, 
-0.4699, 
-0.4630, 
-0.4542, 
-0.4420, 
-0.4267, 
-0.4114, 
-0.3982, 
-0.3907, 
-0.3892, 
-0.3900, 
-0.3902, 
-0.3886, 
-0.3862, 
-0.3860, 
-0.3874, 
-0.3888, 
-0.3877, 
-0.3840, 
-0.3807, 
-0.3790, 
-0.3794, 
-0.3803, 
-0.3793, 
-0.3788, 
-0.3808, 
-0.3852, 
-0.3908, 
-0.3934, 
-0.3913, 
-0.3867, 
-0.3824, 
-0.3817, 
-0.3848, 
-0.3877, 
-0.3880, 
-0.3846, 
-0.3788, 
-0.3755, 
-0.3775, 
-0.3841, 
-0.3935, 
-0.4014, 
-0.4065, 
-0.4097, 
-0.4112, 
-0.4115, 
-0.4103, 
-0.4065, 
-0.4028, 
-0.4005, 
-0.3988, 
-0.3973, 
-0.3943, 
-0.3910, 
-0.3909, 
-0.3946, 
-0.4005, 
-0.4047, 
-0.4037, 
-0.3995, 
-0.3951, 
-0.3915, 
-0.3887, 
-0.3847, 
-0.3795, 
-0.3770, 
-0.3789, 
-0.3841, 
-0.3894, 
-0.3909, 
-0.3900, 
-0.3903, 
-0.3932, 
-0.3993, 
-0.4051, 
-0.4079, 
-0.4090, 
-0.4096, 
-0.4098, 
-0.4089, 
-0.4045, 
-0.3974, 
-0.3908, 
-0.3869, 
-0.3874, 
-0.3906, 
-0.3928, 
-0.3940, 
-0.3949, 
-0.3974, 
-0.4034, 
-0.4104, 
-0.4150, 
-0.4149, 
-0.4094, 
-0.4030, 
-0.4003, 
-0.4017, 
-0.4063, 
-0.4099, 
-0.4095, 
-0.4071, 
-0.4052, 
-0.4059, 
-0.4094, 
-0.4128, 
-0.4146, 
-0.4151, 
-0.4138, 
-0.4122, 
-0.4101, 
-0.4064, 
-0.4030, 
-0.4005, 
-0.3991, 
-0.3993, 
-0.3991, 
-0.3977, 
-0.3955, 
-0.3922, 
-0.3900, 
-0.3903, 
-0.3928, 
-0.3986, 
-0.4055, 
-0.4102, 
-0.4111, 
-0.4068, 
-0.3991, 
-0.3919, 
-0.3877, 
-0.3874, 
-0.3898, 
-0.3906, 
-0.3887, 
-0.3849, 
-0.3811, 
-0.3817, 
-0.3876, 
-0.3968, 
-0.4063, 
-0.4115, 
-0.4108, 
-0.4059, 
-0.3994, 
-0.3954, 
-0.3953, 
-0.3955, 
-0.3940, 
-0.3891, 
-0.3820, 
-0.3776, 
-0.3782, 
-0.3829, 
-0.3891, 
-0.3927, 
-0.3938, 
-0.3955, 
-0.3990, 
-0.4048, 
-0.4100, 
-0.4103, 
-0.4059, 
-0.3987, 
-0.3924, 
-0.3901, 
-0.3905, 
-0.3912, 
-0.3904, 
-0.3870, 
-0.3842, 
-0.3853, 
-0.3899, 
-0.3976, 
-0.4052, 
-0.4099, 
-0.4127, 
-0.4141, 
-0.4146, 
-0.4142, 
-0.4111, 
-0.4058, 
-0.4006, 
-0.3961, 
-0.3945, 
-0.3956, 
-0.3976, 
-0.4011, 
-0.4055, 
-0.4099, 
-0.4143, 
-0.4173, 
-0.4189, 
-0.4200, 
-0.4204, 
-0.4206, 
-0.4203, 
-0.4175, 
-0.4137, 
-0.4102, 
-0.4086, 
-0.4113, 
-0.4170, 
-0.4223, 
-0.4247, 
-0.4230, 
-0.4202, 
-0.4205, 
-0.4242, 
-0.4303, 
-0.4350, 
-0.4350, 
-0.4325, 
-0.4299, 
-0.4286, 
-0.4288, 
-0.4277, 
-0.4246, 
-0.4214, 
-0.4201, 
-0.4231, 
-0.4303, 
-0.4379, 
-0.4447, 
-0.4495, 
-0.4519, 
-0.4537, 
-0.4545, 
-0.4533, 
-0.4501, 
-0.4445, 
-0.4386, 
-0.4357, 
-0.4361, 
-0.4401, 
-0.4454, 
-0.4484, 
-0.4495, 
-0.4496, 
-0.4505, 
-0.4547, 
-0.4608, 
-0.4664, 
-0.4694, 
-0.4679, 
-0.4640, 
-0.4603, 
-0.4573, 
-0.4561, 
-0.4553, 
-0.4533, 
-0.4515, 
-0.4507, 
-0.4517, 
-0.4554, 
-0.4598, 
-0.4648, 
-0.4700, 
-0.4735, 
-0.4755, 
-0.4748, 
-0.4707, 
-0.4654, 
-0.4600, 
-0.4549, 
-0.4510, 
-0.4475, 
-0.4451, 
-0.4448, 
-0.4446, 
-0.4434, 
-0.4403, 
-0.4356, 
-0.4338, 
-0.4364, 
-0.4405, 
-0.4417, 
-0.4358, 
-0.4238, 
-0.4118, 
-0.4033, 
-0.3989, 
-0.3949, 
-0.3873, 
-0.3779, 
-0.3704, 
-0.3665, 
-0.3659, 
-0.3652, 
-0.3627, 
-0.3610, 
-0.3613, 
-0.3632, 
-0.3638, 
-0.3590, 
-0.3499, 
-0.3402, 
-0.3324, 
-0.3282, 
-0.3256, 
-0.3219, 
-0.3181, 
-0.3157, 
-0.3161, 
-0.3197, 
-0.3240, 
-0.3276, 
-0.3300, 
-0.3306, 
-0.3306, 
-0.3300, 
-0.3277, 
-0.3242, 
-0.3195, 
-0.3142, 
-0.3101, 
-0.3068, 
-0.3038, 
-0.3008, 
-0.2977, 
-0.2968, 
-0.3002, 
-0.3065, 
-0.3140, 
-0.3195, 
-0.3212, 
-0.3208, 
-0.3194, 
-0.3176, 
-0.3151, 
-0.3112, 
-0.3071, 
-0.3052, 
-0.3052, 
-0.3059, 
-0.3049, 
-0.3006, 
-0.2966, 
-0.2970, 
-0.3038, 
-0.3159, 
-0.3275, 
-0.3328, 
-0.3300, 
-0.3206, 
-0.3107, 
-0.3052, 
-0.3047, 
-0.3077, 
-0.3100, 
-0.3085, 
-0.3042, 
-0.2997, 
-0.2978, 
-0.3006, 
-0.3065, 
-0.3135, 
-0.3198, 
-0.3236, 
-0.3253, 
-0.3248, 
-0.3212, 
-0.3158, 
-0.3098, 
-0.3054, 
-0.3053, 
-0.3087, 
-0.3128, 
-0.3146, 
-0.3121, 
-0.3077, 
-0.3052, 
-0.3061, 
-0.3105, 
-0.3152, 
-0.3171, 
-0.3163, 
-0.3139, 
-0.3114, 
-0.3093, 
-0.3060, 
-0.3010, 
-0.2956, 
-0.2907, 
-0.2888, 
-0.2907, 
-0.2947, 
-0.3001, 
-0.3048, 
-0.3080, 
-0.3105, 
-0.3129, 
-0.3158, 
-0.3192, 
-0.3208, 
-0.3195, 
-0.3152, 
-0.3085, 
-0.3030, 
-0.3012, 
-0.3035, 
-0.3094, 
-0.3151, 
-0.3175, 
-0.3162, 
-0.3127, 
-0.3114, 
-0.3151, 
-0.3218, 
-0.3279, 
-0.3295, 
-0.3252, 
-0.3194, 
-0.3160, 
-0.3163, 
-0.3186, 
-0.3194, 
-0.3178, 
-0.3161, 
-0.3162, 
-0.3197, 
-0.3252, 
-0.3295, 
-0.3326, 
-0.3348, 
-0.3367, 
-0.3387, 
-0.3394, 
-0.3381, 
-0.3359, 
-0.3338, 
-0.3335, 
-0.3349, 
-0.3353, 
-0.3336, 
-0.3298, 
-0.3252, 
-0.3238, 
-0.3273, 
-0.3345, 
-0.3429, 
-0.3485, 
-0.3503, 
-0.3500, 
-0.3486, 
-0.3471, 
-0.3452, 
-0.3416, 
-0.3380, 
-0.3354, 
-0.3333, 
-0.3318, 
-0.3299, 
-0.3286, 
-0.3305, 
-0.3351, 
-0.3409, 
-0.3450, 
-0.3454, 
-0.3446, 
-0.3453, 
-0.3469, 
-0.3473, 
-0.3430, 
-0.3338, 
-0.3244, 
-0.3197, 
-0.3219, 
-0.3289, 
-0.3348, 
-0.3366, 
-0.3352, 
-0.3332, 
-0.3351, 
-0.3414, 
-0.3484, 
-0.3528, 
-0.3515, 
-0.3448, 
-0.3369, 
-0.3308, 
-0.3287, 
-0.3300, 
-0.3312, 
-0.3311, 
-0.3300, 
-0.3289, 
-0.3310, 
-0.3368, 
-0.3446, 
-0.3529, 
-0.3585, 
-0.3607, 
-0.3602, 
-0.3579, 
-0.3560, 
-0.3552, 
-0.3541, 
-0.3526, 
-0.3497, 
-0.3456, 
-0.3425, 
-0.3412, 
-0.3419, 
-0.3444, 
-0.3461, 
-0.3463, 
-0.3454, 
-0.3437, 
-0.3436, 
-0.3454, 
-0.3470, 
-0.3469, 
-0.3436, 
-0.3375, 
-0.3319, 
-0.3285, 
-0.3281, 
-0.3300, 
-0.3318, 
-0.3333, 
-0.3352, 
-0.3374, 
-0.3411, 
-0.3452, 
-0.3478, 
-0.3492, 
-0.3492, 
-0.3489, 
-0.3491, 
-0.3483, 
-0.3454, 
-0.3405, 
-0.3341, 
-0.3302, 
-0.3308, 
-0.3349, 
-0.3406, 
-0.3443, 
-0.3453, 
-0.3459, 
-0.3478, 
-0.3511, 
-0.3544, 
-0.3548, 
-0.3529, 
-0.3502, 
-0.3470, 
-0.3439, 
-0.3398, 
-0.3348, 
-0.3318, 
-0.3321, 
-0.3352, 
-0.3392, 
-0.3409, 
-0.3406, 
-0.3402, 
-0.3402, 
-0.3408, 
-0.3400, 
-0.3365, 
-0.3327, 
-0.3309, 
-0.3314, 
-0.3337, 
-0.3345, 
-0.3331, 
-0.3309, 
-0.3296, 
-0.3312, 
-0.3352, 
-0.3393, 
-0.3427, 
-0.3447, 
-0.3452, 
-0.3453, 
-0.3447, 
-0.3428, 
-0.3401, 
-0.3365, 
-0.3329, 
-0.3300, 
-0.3263, 
-0.3215, 
-0.3149, 
-0.3066, 
-0.3000, 
-0.2966, 
-0.2966, 
-0.2986, 
-0.2996, 
-0.2983, 
-0.2952, 
-0.2912, 
-0.2878, 
-0.2852, 
-0.2819, 
-0.2786, 
-0.2750, 
-0.2711, 
-0.2680, 
-0.2655, 
-0.2642, 
-0.2647, 
-0.2658, 
-0.2662, 
-0.2651, 
-0.2615, 
-0.2578, 
-0.2553, 
-0.2536, 
-0.2522, 
-0.2494, 
-0.2448, 
-0.2399, 
-0.2352, 
-0.2306, 
-0.2256, 
-0.2196, 
-0.2151, 
-0.2151, 
-0.2205, 
-0.2303, 
-0.2402, 
-0.2456, 
-0.2459, 
-0.2426, 
-0.2396, 
-0.2399, 
-0.2426, 
-0.2451, 
-0.2450, 
-0.2413, 
-0.2371, 
-0.2355, 
-0.2370, 
-0.2411, 
-0.2452, 
-0.2481, 
-0.2516, 
-0.2572, 
-0.2651, 
-0.2736, 
-0.2786, 
-0.2787, 
-0.2752, 
-0.2701, 
-0.2669, 
-0.2656, 
-0.2630, 
-0.2573, 
-0.2474, 
-0.2358, 
-0.2266, 
-0.2216, 
-0.2202, 
-0.2204, 
-0.2208, 
-0.2234, 
-0.2308, 
-0.2420, 
-0.2544, 
-0.2637, 
-0.2682, 
-0.2705, 
-0.2731, 
-0.2767, 
-0.2800, 
-0.2812, 
-0.2819, 
-0.2852, 
-0.2911, 
-0.2986, 
-0.3048, 
-0.3088, 
-0.3138, 
-0.3217, 
-0.3310, 
-0.3380, 
-0.3387, 
-0.3346, 
-0.3306, 
-0.3298, 
-0.3324, 
-0.3352, 
-0.3350, 
-0.3342, 
-0.3362, 
-0.3427, 
-0.3528, 
-0.3622, 
-0.3677, 
-0.3695, 
-0.3680, 
-0.3647, 
-0.3602, 
-0.3541, 
-0.3488, 
-0.3458, 
-0.3455, 
-0.3477, 
-0.3505, 
-0.3528, 
-0.3553, 
-0.3581, 
-0.3614, 
-0.3652, 
-0.3682, 
-0.3714, 
-0.3752, 
-0.3782, 
-0.3799, 
-0.3789, 
-0.3751, 
-0.3710, 
-0.3676, 
-0.3658, 
-0.3653, 
-0.3644, 
-0.3639, 
-0.3652, 
-0.3682, 
-0.3739, 
-0.3803, 
-0.3842, 
-0.3851, 
-0.3832, 
-0.3805, 
-0.3796, 
-0.3795, 
-0.3786, 
-0.3751, 
-0.3676, 
-0.3598, 
-0.3557, 
-0.3563, 
-0.3625, 
-0.3715, 
-0.3804, 
-0.3889, 
-0.3961, 
-0.4015, 
-0.4051, 
-0.4063, 
-0.4072, 
-0.4103, 
-0.4163, 
-0.4254, 
-0.4357, 
-0.4456, 
-0.4553, 
-0.4656, 
-0.4776, 
-0.4899, 
-0.5012, 
-0.5115, 
-0.5207, 
-0.5310, 
-0.5433, 
-0.5554, 
-0.5660, 
-0.5708, 
-0.5660, 
-0.5502, 
-0.5229, 
-0.4866, 
-0.4461, 
-0.4036, 
-0.3576, 
-0.3065, 
-0.2502, 
-0.1921, 
-0.1392, 
-0.0911, 
-0.0373, 
0.0359, 
0.1385, 
0.2659, 
0.3993, 
0.5194, 
0.6152, 
0.6902, 
0.7568, 
0.8225, 
0.8850, 
0.9341, 
0.9561, 
0.9453, 
0.9041, 
0.8378, 
0.7517, 
0.6456, 
0.5171, 
0.3689, 
0.2087, 
0.0500, 
-0.0929, 
-0.2141, 
-0.3127, 
-0.3904, 
-0.4494, 
-0.4881, 
-0.5051, 
-0.5028, 
-0.4868, 
-0.4654, 
-0.4460, 
-0.4320, 
-0.4225, 
-0.4157, 
-0.4092, 
-0.4018, 
-0.3959, 
-0.3920, 
-0.3907, 
-0.3922, 
-0.3938, 
-0.3948, 
-0.3949, 
-0.3928, 
-0.3903, 
-0.3891, 
-0.3910, 
-0.3962, 
-0.4017, 
-0.4043, 
-0.4022, 
-0.3977, 
-0.3959, 
-0.3981, 
-0.4025, 
-0.4048, 
-0.4011, 
-0.3948, 
-0.3904, 
-0.3898, 
-0.3926, 
-0.3952, 
-0.3955, 
-0.3963, 
-0.3992, 
-0.4043, 
-0.4092, 
-0.4101, 
-0.4079, 
-0.4053, 
-0.4029, 
-0.4017, 
-0.4000, 
-0.3977, 
-0.3981, 
-0.4025, 
-0.4089, 
-0.4136, 
-0.4128, 
-0.4084, 
-0.4058, 
-0.4077, 
-0.4140, 
-0.4202, 
-0.4215, 
-0.4187, 
-0.4140, 
-0.4094, 
-0.4062, 
-0.4038, 
-0.4029, 
-0.4053, 
-0.4103, 
-0.4163, 
-0.4203, 
-0.4201, 
-0.4192, 
-0.4208, 
-0.4252, 
-0.4309, 
-0.4332, 
-0.4294, 
-0.4218, 
-0.4139, 
-0.4096, 
-0.4100, 
-0.4115, 
-0.4119, 
-0.4098, 
-0.4059, 
-0.4043, 
-0.4071, 
-0.4138, 
-0.4225, 
-0.4290, 
-0.4312, 
-0.4301, 
-0.4264, 
-0.4227, 
-0.4203, 
-0.4179, 
-0.4164, 
-0.4152, 
-0.4134, 
-0.4117, 
-0.4101, 
-0.4092, 
-0.4108, 
-0.4144, 
-0.4195, 
-0.4246, 
-0.4264, 
-0.4246, 
-0.4197, 
-0.4124, 
-0.4058, 
-0.4008, 
-0.3973, 
-0.3960, 
-0.3959, 
-0.3970, 
-0.3996, 
-0.4015, 
-0.4019, 
-0.4003, 
-0.3965, 
-0.3944, 
-0.3963, 
-0.4016, 
-0.4089, 
-0.4136, 
-0.4125, 
-0.4063, 
-0.3976, 
-0.3912, 
-0.3904, 
-0.3933, 
-0.3975, 
-0.3999, 
-0.3992, 
-0.3989, 
-0.4012, 
-0.4066, 
-0.4137, 
-0.4194, 
-0.4227, 
-0.4249, 
-0.4259, 
-0.4263, 
-0.4253, 
-0.4215, 
-0.4177, 
-0.4156, 
-0.4150, 
-0.4154, 
-0.4144, 
-0.4122, 
-0.4115, 
-0.4135, 
-0.4187, 
-0.4247, 
-0.4276, 
-0.4272, 
-0.4249, 
-0.4220, 
-0.4208, 
-0.4205, 
-0.4187, 
-0.4152, 
-0.4096, 
-0.4039, 
-0.4006, 
-0.3992, 
-0.3993, 
-0.4003, 
-0.4011, 
-0.4046, 
-0.4110, 
-0.4179, 
-0.4226, 
-0.4218, 
-0.4165, 
-0.4110, 
-0.4075, 
-0.4063, 
-0.4051, 
-0.4014, 
-0.3973, 
-0.3955, 
-0.3962, 
-0.3986, 
-0.3997, 
-0.3990, 
-0.3998, 
-0.4026, 
-0.4054, 
-0.4047
};
const uint16_t ecg_resampled_integer[1024] = { 
 636, 
 628, 
 630, 
 629, 
 629, 
 631, 
 628, 
 650, 
 651, 
 631, 
 627, 
 613, 
 618, 
 611, 
 595, 
 586, 
 585, 
 610, 
 609, 
 592, 
 580, 
 582, 
 607, 
 639, 
 617, 
 579, 
 555, 
 531, 
 530, 
 506, 
 505, 
 482, 
 475, 
 476, 
 483, 
 496, 
 488, 
 475, 
 460, 
 459, 
 458, 
 460, 
 462, 
 445, 
 455, 
 474, 
 475, 
 473, 
 462, 
 445, 
 454, 
 452, 
 464, 
 455, 
 440, 
 427, 
 414, 
 385, 
 355, 
 345, 
 330, 
 265, 
 231, 
 232, 
 314, 
 455, 
 594, 
 797, 
1035, 
1407, 
1670, 
1771, 
1736, 
1419, 
1001, 
 620, 
 389, 
 297, 
 319, 
 382, 
 411, 
 411, 
 395, 
 405, 
 414, 
 425, 
 432, 
 423, 
 404, 
 408, 
 408, 
 396, 
 409, 
 408, 
 409, 
 415, 
 413, 
 411, 
 393, 
 386, 
 403, 
 420, 
 431, 
 424, 
 419, 
 406, 
 403, 
 401, 
 395, 
 385, 
 382, 
 397, 
 410, 
 411, 
 409, 
 393, 
 399, 
 416, 
 414, 
 411, 
 407, 
 405, 
 403, 
 407, 
 399, 
 388, 
 383, 
 387, 
 399, 
 416, 
 415, 
 409, 
 400, 
 404, 
 408, 
 403, 
 397, 
 390, 
 386, 
 396, 
 402, 
 408, 
 402, 
 388, 
 390, 
 401, 
 406, 
 404, 
 391, 
 381, 
 384, 
 391, 
 397, 
 397, 
 384, 
 376, 
 375, 
 372, 
 373, 
 368, 
 353, 
 360, 
 376, 
 380, 
 373, 
 358, 
 362, 
 369, 
 372, 
 375, 
 372, 
 366, 
 376, 
 405, 
 417, 
 415, 
 406, 
 405, 
 433, 
 447, 
 450, 
 456, 
 456, 
 463, 
 472, 
 491, 
 506, 
 502, 
 493, 
 499, 
 518, 
 522, 
 512, 
 507, 
 500, 
 510, 
 511, 
 502, 
 506, 
 503, 
 504, 
 504, 
 490, 
 493, 
 492, 
 486, 
 484, 
 492, 
 482, 
 472, 
 462, 
 470, 
 484, 
 489, 
 474, 
 466, 
 470, 
 475, 
 480, 
 486, 
 470, 
 460, 
 465, 
 474, 
 467, 
 466, 
 449, 
 445, 
 445, 
 450, 
 442, 
 434, 
 439, 
 448, 
 460, 
 465, 
 459, 
 451, 
 439, 
 455, 
 452, 
 443, 
 441, 
 426, 
 423, 
 444, 
 454, 
 445, 
 418, 
 414, 
 428, 
 446, 
 441, 
 431, 
 419, 
 411, 
 422, 
 434, 
 438, 
 442, 
 435, 
 443, 
 444, 
 455, 
 448, 
 444, 
 441, 
 444, 
 466, 
 462, 
 443, 
 433, 
 434, 
 452, 
 458, 
 470, 
 481, 
 477, 
 477, 
 489, 
 509, 
 501, 
 522, 
 541, 
 551, 
 565, 
 558, 
 547, 
 530, 
 540, 
 534, 
 536, 
 533, 
 527, 
 521, 
 519, 
 536, 
 549, 
 554, 
 512, 
 465, 
 463, 
 447, 
 426, 
 410, 
 412, 
 423, 
 426, 
 426, 
 423, 
 404, 
 394, 
 400, 
 397, 
 391, 
 388, 
 389, 
 413, 
 403, 
 421, 
 405, 
 382, 
 393, 
 410, 
 417, 
 410, 
 387, 
 372, 
 373, 
 331, 
 292, 
 256, 
 210, 
 175, 
 187, 
 275, 
 443, 
 615, 
 785, 
1106, 
1487, 
1719, 
1867, 
1906, 
1780, 
1491, 
1125, 
 777, 
 484, 
 342, 
 271, 
 244, 
 266, 
 315, 
 339, 
 342, 
 341, 
 347, 
 353, 
 352, 
 341, 
 345, 
 345, 
 349, 
 351, 
 327, 
 316, 
 321, 
 329, 
 339, 
 328, 
 329, 
 344, 
 355, 
 343, 
 337, 
 325, 
 315, 
 325, 
 341, 
 337, 
 329, 
 313, 
 323, 
 321, 
 320, 
 317, 
 311, 
 318, 
 326, 
 330, 
 337, 
 334, 
 319, 
 331, 
 340, 
 344, 
 345, 
 320, 
 324, 
 332, 
 344, 
 349, 
 340, 
 327, 
 321, 
 335, 
 340, 
 344, 
 331, 
 314, 
 313, 
 327, 
 332, 
 321, 
 309, 
 304, 
 309, 
 314, 
 304, 
 302, 
 294, 
 290, 
 295, 
 302, 
 291, 
 272, 
 264, 
 276, 
 282, 
 273, 
 266, 
 251, 
 253, 
 261, 
 267, 
 262, 
 247, 
 243, 
 257, 
 271, 
 277, 
 283, 
 284, 
 299, 
 329, 
 352, 
 369, 
 372, 
 375, 
 397, 
 417, 
 426, 
 419, 
 411, 
 415, 
 429, 
 443, 
 446, 
 432, 
 422, 
 429, 
 438, 
 443, 
 444, 
 420, 
 422, 
 438, 
 439, 
 446, 
 432, 
 419, 
 429, 
 438, 
 433, 
 437, 
 431, 
 429, 
 441, 
 454, 
 452, 
 437, 
 428, 
 426, 
 440, 
 436, 
 427, 
 427, 
 416, 
 424, 
 426, 
 424, 
 413, 
 403, 
 401, 
 406, 
 408, 
 414, 
 400, 
 387, 
 395, 
 404, 
 411, 
 404, 
 394, 
 393, 
 405, 
 418, 
 405, 
 403, 
 387, 
 397, 
 413, 
 409, 
 403, 
 380, 
 378, 
 383, 
 391, 
 398, 
 392, 
 394, 
 393, 
 406, 
 411, 
 404, 
 394, 
 387, 
 391, 
 404, 
 405, 
 392, 
 387, 
 385, 
 395, 
 408, 
 403, 
 398, 
 401, 
 409, 
 408, 
 409, 
 401, 
 392, 
 396, 
 408, 
 421, 
 446, 
 451, 
 451, 
 465, 
 475, 
 488, 
 487, 
 492, 
 501, 
 511, 
 529, 
 544, 
 529, 
 510, 
 517, 
 513, 
 522, 
 512, 
 496, 
 474, 
 481, 
 491, 
 519, 
 541, 
 535, 
 502, 
 479, 
 473, 
 461, 
 443, 
 420, 
 403, 
 409, 
 406, 
 396, 
 367, 
 370, 
 389, 
 391, 
 380, 
 370, 
 357, 
 354, 
 366, 
 370, 
 365, 
 347, 
 351, 
 354, 
 375, 
 373, 
 340, 
 323, 
 315, 
 287, 
 250, 
 209, 
 173, 
 132, 
 152, 
 272, 
 441, 
 634, 
 848, 
1276, 
1619, 
1845, 
1915, 
1695, 
1238, 
 694, 
 345, 
 205, 
 250, 
 302, 
 325, 
 340, 
 333, 
 341, 
 330, 
 329, 
 329, 
 328, 
 339, 
 334, 
 323, 
 318, 
 328, 
 327, 
 313, 
 320, 
 307, 
 312, 
 326, 
 315, 
 306, 
 297, 
 297, 
 315, 
 315, 
 321, 
 299, 
 293, 
 305, 
 310, 
 317, 
 310, 
 299, 
 314, 
 332, 
 331, 
 327, 
 333, 
 318, 
 323, 
 337, 
 330, 
 324, 
 306, 
 298, 
 304, 
 309, 
 315, 
 305, 
 298, 
 303, 
 311, 
 327, 
 328, 
 314, 
 307, 
 317, 
 327, 
 331, 
 329, 
 323, 
 338, 
 335, 
 335, 
 340, 
 326, 
 315, 
 321, 
 321, 
 314, 
 308, 
 305, 
 301, 
 306, 
 312, 
 312, 
 293, 
 290, 
 290, 
 302, 
 305, 
 305, 
 302, 
 299, 
 305, 
 326, 
 334, 
 338, 
 352, 
 376, 
 397, 
 405, 
 409, 
 405, 
 410, 
 418, 
 429, 
 440, 
 433, 
 432, 
 439, 
 445, 
 447, 
 445, 
 436, 
 435, 
 432, 
 436, 
 444, 
 434, 
 425, 
 419, 
 428, 
 439, 
 438, 
 423, 
 422, 
 434, 
 443, 
 445, 
 429, 
 415, 
 417, 
 423, 
 423, 
 417, 
 394, 
 389, 
 398, 
 405, 
 409, 
 404, 
 390, 
 380, 
 387, 
 384, 
 378, 
 379, 
 375, 
 378, 
 390, 
 394, 
 387, 
 379, 
 370, 
 376, 
 386, 
 383, 
 373, 
 356, 
 360, 
 372, 
 372, 
 374, 
 368, 
 356, 
 364, 
 376, 
 387, 
 387, 
 373, 
 367, 
 384, 
 395, 
 394, 
 383, 
 371, 
 376, 
 381, 
 381, 
 374, 
 353, 
 360, 
 380, 
 378, 
 379, 
 372, 
 368, 
 375, 
 390, 
 385, 
 392, 
 394, 
 394, 
 414, 
 440, 
 440, 
 438, 
 437, 
 455, 
 466, 
 473, 
 471, 
 471, 
 481, 
 491, 
 505, 
 505, 
 488, 
 482, 
 471, 
 482, 
 483, 
 475, 
 471, 
 475, 
 472, 
 480, 
 491, 
 507, 
 502, 
 479, 
 445, 
 435, 
 404, 
 371, 
 356, 
 345, 
 357, 
 362, 
 354, 
 344, 
 338, 
 341, 
 347, 
 346, 
 336, 
 324, 
 330, 
 356, 
 357, 
 339, 
 326, 
 313, 
 326, 
 336, 
 330, 
 307, 
 271, 
 237, 
 207, 
 196, 
 180, 
 140, 
  71, 
  41, 
  70, 
 166, 
 303, 
 438, 
 589, 
 895, 
1243, 
1543, 
1764, 
1805, 
1608, 
1204, 
 725, 
 326, 
 178, 
 222, 
 290, 
 338, 
 337, 
 330, 
 314, 
 325, 
 345, 
 338, 
 331, 
 319, 
 320, 
 326, 
 336, 
 338, 
 318, 
 310, 
 317, 
 332, 
 323, 
 317, 
 325, 
 317, 
 328, 
 347, 
 341, 
 337, 
 329, 
 329, 
 328, 
 335, 
 332, 
 321, 
 324, 
 330, 
 337, 
 353, 
 352, 
 336, 
 338, 
 346, 
 357, 
 346, 
 335, 
 336, 
 351, 
 358, 
 355, 
 338, 
 338, 
 339, 
 359, 
 364, 
 344, 
 337, 
 349, 
 349, 
 359, 
 346, 
 344, 
 354, 
 357, 
 358, 
 357, 
 355, 
 339, 
 343, 
 366, 
 364, 
 356, 
 343, 
 341, 
 344, 
 368, 
 354, 
 349, 
 345, 
 350, 
 360, 
 367, 
 364, 
 343, 
 338, 
 346, 
 352, 
 366, 
 366, 
 359, 
 377, 
 400, 
 422, 
 428, 
 423, 
 419, 
 433, 
 458, 
 457, 
 448, 
 460, 
 464, 
 468, 
 478, 
 474, 
 459, 
 454, 
 452, 
 462, 
 466, 
 457, 
 446, 
 441, 
 459, 
 468, 
 474, 
 460, 
 442, 
 447, 
 451, 
 455, 
 457, 
 445, 
 443, 
 449, 
 449, 
 442, 
 433, 
 432, 
 433, 
 447, 
 446, 
 433, 
 411, 
 403, 
 416, 
 422, 
 425, 
 422, 
 409, 
 409, 
 422, 
 425
};
