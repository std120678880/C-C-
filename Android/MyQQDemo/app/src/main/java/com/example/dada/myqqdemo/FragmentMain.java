package com.example.dada.myqqdemo;

import android.annotation.SuppressLint;
import android.support.v4.app.FragmentActivity;
import android.support.v4.app.FragmentTabHost;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.ImageView;
import android.widget.TabHost;

import butterknife.Bind;
import butterknife.ButterKnife;

public class FragmentMain extends FragmentActivity {

    private FragmentTabHost fragmentTabHost;

    private String texts[] = {"消息","电话","联系人","动态"};

    private int ImageButtons[] = {
            R.drawable.bt_message_selector,
            R.drawable.bt_phone_selector,
            R.drawable.bt_contact_selector,
            R.drawable.bt_dynamic_selector
    };

    private Class fragmentClass[] = {
            Message_Fragment.class,
            Phone_Fragment.class,
            Contact_Fragment.class,
            Dynamic_Fragment.class
    };

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_fragment_main);

        fragmentTabHost = (FragmentTabHost)findViewById(android.R.id.tabhost);
        fragmentTabHost.setup(this, getSupportFragmentManager(),R.id.maincontent);

        for (int i = 0; i < ImageButtons.length; i++) {

            TabHost.TabSpec spec = fragmentTabHost.newTabSpec(texts[i]).setIndicator(getView(i));

            fragmentTabHost.addTab(spec, fragmentClass[i], null);

            fragmentTabHost.getTabWidget().getChildAt(i).setBackgroundResource(R.drawable.block);
        }
    }

    private View getView(int i){
        View view = View.inflate(FragmentMain.this, R.layout.tabcontent, null);

        ImageView imageView = (ImageView)view.findViewById(R.id.tab_Image);

        imageView.setImageResource(ImageButtons[i]);

        return view;
    }
}