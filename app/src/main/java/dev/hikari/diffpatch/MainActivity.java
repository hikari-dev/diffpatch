package dev.hikari.diffpatch;

import android.Manifest;
import android.annotation.SuppressLint;
import android.os.Bundle;

import androidx.activity.result.ActivityResultLauncher;
import androidx.activity.result.contract.ActivityResultContracts;
import androidx.appcompat.app.AppCompatActivity;

import java.util.Map;

import dev.hikari.diffpatch.databinding.ActivityMainBinding;

public class MainActivity extends AppCompatActivity {

    private ActivityMainBinding binding;

    @SuppressLint({"SetTextI18n", "SdCardPath"})
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        binding = ActivityMainBinding.inflate(getLayoutInflater());
        setContentView(binding.getRoot());

        ActivityResultLauncher<String[]> permissionsLauncher = registerForActivityResult(new ActivityResultContracts.RequestMultiplePermissions(), result -> {
            for (Map.Entry<String, Boolean> entry : result.entrySet()) {
                if (!entry.getValue()) {
                    finish();
                }
            }

            binding.button1.setOnClickListener(v -> {
                binding.button1.setEnabled(false);
                new Thread(() -> {
                    int ret = DiffPatchUtils.diff("/sdcard/1.txt", "/sdcard/2.txt", "/sdcard/1to2.patch");
                    runOnUiThread(() -> {
                        if (ret == 0) {
                            binding.textView.setText("Diff Success");
                        } else {
                            binding.textView.setText("Diff Failed");
                        }
                        binding.button1.setEnabled(true);
                    });
                }).start();

            });

            binding.button2.setOnClickListener(v -> {
                binding.button2.setEnabled(false);
                new Thread(() -> {
                    int ret = DiffPatchUtils.patch("/sdcard/1.txt", "/sdcard/3.txt", "/sdcard/1to2.patch");
                    runOnUiThread(() -> {
                        if (ret == 0) {
                            binding.textView.setText("Patch Success");
                        } else {
                            binding.textView.setText("Patch Failed");
                        }
                        binding.button2.setEnabled(true);
                    });
                }).start();
            });
        });

        permissionsLauncher.launch(new String[]{
                Manifest.permission.READ_EXTERNAL_STORAGE,
                Manifest.permission.WRITE_EXTERNAL_STORAGE
        });
    }

}