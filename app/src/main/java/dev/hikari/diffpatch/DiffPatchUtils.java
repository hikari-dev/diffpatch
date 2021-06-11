package dev.hikari.diffpatch;

public class DiffPatchUtils {

    static {
        System.loadLibrary("diffpatch");
    }

    /**
     * native方法 比较路径为oldPath的文件与newPath的文件之间差异，并生成patch包
     *
     * @param oldPath   示例:/sdcard/old.apk
     * @param newPath   示例:/sdcard/new.apk
     * @param patchPath 示例:/sdcard/diff.patch
     * @return 0代表操作成功
     */
    public static native int diff(String oldPath, String newPath, String patchPath);


    /**
     * native方法 使用路径为oldPath的文件与路径为patchPath的补丁包，合成新的文件，并存储于newPath
     *
     * @param oldPath   示例:/sdcard/old.apk
     * @param newPath   示例:/sdcard/new.apk
     * @param patchPath 示例:/sdcard/diff.patch
     * @return 0代表操作成功
     */
    public static native int patch(String oldPath, String newPath, String patchPath);
}
