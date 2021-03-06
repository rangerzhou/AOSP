/*
 * Copyright (C) 2020 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

package com.android.xsdc.tag;

import com.android.xsdc.XsdParserException;

import java.util.Collections;
import java.util.List;
import javax.xml.namespace.QName;

public class XsdGroup extends XsdTag {
    final private List<XsdElement> elements;

    public XsdGroup(String name, QName ref, List<XsdElement> elements)
            throws XsdParserException {
        super(name, ref);
        if (name == null && ref == null) {
            throw new XsdParserException("name and ref cannot be both null");
        }
        this.elements = Collections.unmodifiableList(elements);
    }

    public List<XsdElement> getElements() {
        return elements;
    }
}
