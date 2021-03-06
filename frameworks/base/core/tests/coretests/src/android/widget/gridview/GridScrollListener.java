/*
 * Copyright (C) 2007 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

package android.widget.gridview;

import android.app.Activity;
import android.os.Bundle;
import android.os.Handler;
import android.widget.AbsListView;
import android.widget.ArrayAdapter;
import android.widget.GridView;
import android.widget.TextView;

import com.android.frameworks.coretests.R;

/**
 * Exercises change notification in a list
 */
public class GridScrollListener extends Activity implements AbsListView.OnScrollListener {
    Handler mHandler = new Handler();
    TextView mText;
    GridView mGridView;

    @Override
    public void onCreate(Bundle icicle) {
        super.onCreate(icicle);
        
        setContentView(R.layout.grid_scroll_listener);

        String values[] = new String[1000];
        int i=0;
        for(i=0; i<1000; i++) {
            values[i] = ((Integer)i).toString();
        }
        
        mText = findViewById(R.id.text);
        mGridView = findViewById(R.id.grid);
        mGridView.setAdapter(new ArrayAdapter<String>(this,
                android.R.layout.simple_list_item_1, values));

        mGridView.setOnScrollListener(this);
    }
    
    public GridView getGridView() {
        return mGridView;
    }

    public void onScroll(AbsListView view, int firstVisibleItem, int visibleItemCount, int totalItemCount) {
        int lastItem = firstVisibleItem + visibleItemCount - 1;
        mText.setText("Showing " + firstVisibleItem + "-" + lastItem + "/" + totalItemCount);
    }

    public void onScrollStateChanged(AbsListView view, int scrollState) {        
    }
}
