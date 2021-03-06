/*
 * Copyright (C) 2011 The Android Open Source Project
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

package com.android.test.hwui;

import android.animation.ObjectAnimator;
import android.app.Activity;
import android.content.Context;
import android.content.res.Resources;
import android.graphics.Paint;
import android.graphics.PorterDuff;
import android.graphics.PorterDuffColorFilter;
import android.os.Bundle;
import android.util.DisplayMetrics;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ArrayAdapter;
import android.widget.ListView;
import android.widget.TextView;

@SuppressWarnings({"UnusedDeclaration"})
public class ViewLayersActivity extends Activity {
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        
        setContentView(R.layout.view_layers);

        setupList(R.id.list1);
        setupList(R.id.list2);
        setupList(R.id.list3);

        getWindow().getDecorView().postDelayed(new Runnable() {
            @Override
            public void run() {
                final View leftList = findViewById(R.id.list1);
                final View middleList = findViewById(R.id.list2);
                final View rightList = findViewById(R.id.list3);

                final ObjectAnimator moveRight = ObjectAnimator.ofFloat(leftList,
                        "x", 0, rightList.getLeft());
                moveRight.setDuration(1500);
                moveRight.setRepeatCount(ObjectAnimator.INFINITE);
                moveRight.setRepeatMode(ObjectAnimator.REVERSE);

                final ObjectAnimator moveLeft = ObjectAnimator.ofFloat(rightList,
                        "x", rightList.getLeft(), 0);
                moveLeft.setDuration(1500);
                moveLeft.setRepeatCount(ObjectAnimator.INFINITE);
                moveLeft.setRepeatMode(ObjectAnimator.REVERSE);

                final ObjectAnimator rotate = ObjectAnimator.ofFloat(middleList,
                        "rotationY", 0, 360);
                rotate.setDuration(3000);
                rotate.setRepeatCount(ObjectAnimator.INFINITE);
                rotate.setRepeatMode(ObjectAnimator.REVERSE);

                Paint p = new Paint();
                p.setColorFilter(new PorterDuffColorFilter(0xffff0000, PorterDuff.Mode.MULTIPLY));
                
                Paint p2 = new Paint();
                p2.setAlpha(127);

                Paint p3 = new Paint();
                p3.setColorFilter(new PorterDuffColorFilter(0xff00ff00, PorterDuff.Mode.MULTIPLY));
                
                leftList.setLayerType(View.LAYER_TYPE_SOFTWARE, p);
                leftList.setAlpha(0.5f);
                middleList.setLayerType(View.LAYER_TYPE_HARDWARE, p3);
                middleList.setAlpha(0.5f);
                middleList.setVerticalFadingEdgeEnabled(true);
                rightList.setLayerType(View.LAYER_TYPE_SOFTWARE, p2);

                moveRight.start();
                moveLeft.start();
                rotate.start();

                ((View) leftList.getParent()).setAlpha(0.5f);
            }
        }, 2000);
    }

    private void setupList(int listId) {
        final ListView list = findViewById(listId);
        list.setAdapter(new SimpleListAdapter(this));
    }

    private static class SimpleListAdapter extends ArrayAdapter<String> {
        public SimpleListAdapter(Context context) {
            super(context, android.R.layout.simple_list_item_1, DATA_LIST);
        }

        @Override
        public View getView(int position, View convertView, ViewGroup parent) {
            TextView v = (TextView) super.getView(position, convertView, parent);
            final Resources r = getContext().getResources();
            final DisplayMetrics metrics = r.getDisplayMetrics();
            v.setCompoundDrawablePadding((int) (6 * metrics.density + 0.5f));
            v.setCompoundDrawablesWithIntrinsicBounds(r.getDrawable(R.drawable.icon),
                    null, null, null);
            return v;
        }
    }

    private static final String[] DATA_LIST = {
            "Afghanistan", "Albania", "Algeria", "American Samoa", "Andorra",
            "Angola", "Anguilla", "Antarctica", "Antigua and Barbuda", "Argentina",
            "Armenia", "Aruba", "Australia", "Austria", "Azerbaijan",
            "Bahrain", "Bangladesh", "Barbados", "Belarus", "Belgium",
            "Belize", "Benin", "Bermuda", "Bhutan", "Bolivia",
            "Bosnia and Herzegovina", "Botswana", "Bouvet Island", "Brazil",
            "British Indian Ocean Territory", "British Virgin Islands", "Brunei", "Bulgaria",
            "Burkina Faso", "Burundi", "Cote d'Ivoire", "Cambodia", "Cameroon", "Canada", "Cape Verde",
            "Cayman Islands", "Central African Republic", "Chad", "Chile", "China",
            "Christmas Island", "Cocos (Keeling) Islands", "Colombia", "Comoros", "Congo",
            "Cook Islands", "Costa Rica", "Croatia", "Cuba", "Cyprus", "Czechia",
            "Democratic Republic of the Congo", "Denmark", "Djibouti", "Dominica", "Dominican Republic",
            "East Timor", "Ecuador", "Egypt", "El Salvador", "Equatorial Guinea", "Eritrea",
            "Estonia", "Ethiopia", "Faeroe Islands", "Falkland Islands", "Fiji", "Finland",
            "Former Yugoslav Republic of Macedonia", "France", "French Guiana", "French Polynesia",
            "French Southern Territories", "Gabon", "Georgia", "Germany", "Ghana", "Gibraltar",
            "Greece", "Greenland", "Grenada", "Guadeloupe", "Guam", "Guatemala", "Guinea", "Guinea-Bissau",
            "Guyana", "Haiti", "Heard Island and McDonald Islands", "Honduras", "Hong Kong", "Hungary",
            "Iceland", "India", "Indonesia", "Iran", "Iraq", "Ireland", "Israel", "Italy", "Jamaica",
            "Japan", "Jordan", "Kazakhstan", "Kenya", "Kiribati", "Kuwait", "Kyrgyzstan", "Laos",
            "Latvia", "Lebanon", "Lesotho", "Liberia", "Libya", "Liechtenstein", "Lithuania", "Luxembourg",
            "Macau", "Madagascar", "Malawi", "Malaysia", "Maldives", "Mali", "Malta", "Marshall Islands",
            "Martinique", "Mauritania", "Mauritius", "Mayotte", "Mexico", "Micronesia", "Moldova",
            "Monaco", "Mongolia", "Montserrat", "Morocco", "Mozambique", "Myanmar", "Namibia",
            "Nauru", "Nepal", "Netherlands", "Netherlands Antilles", "New Caledonia", "New Zealand",
            "Nicaragua", "Niger", "Nigeria", "Niue", "Norfolk Island", "North Korea", "Northern Marianas",
            "Norway", "Oman", "Pakistan", "Palau", "Panama", "Papua New Guinea", "Paraguay", "Peru",
            "Philippines", "Pitcairn Islands", "Poland", "Portugal", "Puerto Rico", "Qatar",
            "Reunion", "Romania", "Russia", "Rwanda", "Sqo Tome and Principe", "Saint Helena",
            "Saint Kitts and Nevis", "Saint Lucia", "Saint Pierre and Miquelon",
            "Saint Vincent and the Grenadines", "Samoa", "San Marino", "Saudi Arabia", "Senegal",
            "Seychelles", "Sierra Leone", "Singapore", "Slovakia", "Slovenia", "Solomon Islands",
            "Somalia", "South Africa", "South Georgia and the South Sandwich Islands", "South Korea",
            "Spain", "Sri Lanka", "Sudan", "Suriname", "Svalbard and Jan Mayen", "Swaziland", "Sweden",
            "Switzerland", "Syria", "Taiwan", "Tajikistan", "Tanzania", "Thailand", "The Bahamas",
            "The Gambia", "Togo", "Tokelau", "Tonga", "Trinidad and Tobago", "Tunisia", "Turkey",
            "Turkmenistan", "Turks and Caicos Islands", "Tuvalu", "Virgin Islands", "Uganda",
            "Ukraine", "United Arab Emirates", "United Kingdom",
            "United States", "United States Minor Outlying Islands", "Uruguay", "Uzbekistan",
            "Vanuatu", "Vatican City", "Venezuela", "Vietnam", "Wallis and Futuna", "Western Sahara",
            "Yemen", "Yugoslavia", "Zambia", "Zimbabwe"
    };
}
