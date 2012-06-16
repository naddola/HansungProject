/*
 * Copyright (C) 2008 Google Inc.
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

package com.android.demo.notepad3;

import java.text.SimpleDateFormat;
import java.util.Calendar;

import android.app.Activity;
import android.app.AlarmManager;
import android.content.Intent;
import android.database.Cursor;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;

public class NoteEdit extends Activity {
	//private static final int ACTIVITY_ALRAM=1;
	private EditText mTitleText;
    private EditText mBodyText;
    private Long mRowId;
    private NotesDbAdapter mDbHelper;
    private SimpleDateFormat d = new SimpleDateFormat("yyyy,MM,dd HH:mm:ss");
    Alramd aa=new Alramd();
    
    

    
    
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        mDbHelper = new NotesDbAdapter(this);
        mDbHelper.open();
        setContentView(R.layout.note_edit);
       
        mTitleText = (EditText) findViewById(R.id.title);
        mBodyText = (EditText) findViewById(R.id.body);
      
        Button confirmButton = (Button) findViewById(R.id.confirm);
        Button alarmButton = (Button) findViewById(R.id.Alarm);
       
        mRowId = savedInstanceState != null ? 
        		savedInstanceState.getLong(NotesDbAdapter.KEY_ROWID) : null;
        if (mRowId == null) {
        	Bundle extras = getIntent().getExtras();         
        	mRowId = extras != null ? extras.getLong(NotesDbAdapter.KEY_ROWID) : null;
        }
        
        //alarmButton.set
        final Intent act = new Intent(this, Alramd.class);
        alarmButton.setOnClickListener(new View.OnClickListener() {
			
			public void onClick(View v) {
				 //Intent act = new Intent(this, aa.class);
		            // 인텐트 정보를 이용하여 액티비티를 실행시킨다.
				setResult(RESULT_OK);
				finish();
				startActivity(act);
			}
		});
        
        confirmButton.setOnClickListener(new View.OnClickListener() {

            public void onClick(View view) {
                setResult(RESULT_OK);
                finish();
                
            }
          
        });
        
   
        	
    } 
    
    
    private void populateFields() {
        if (mRowId != null) {
            Cursor note = mDbHelper.fetchNote(mRowId);
            startManagingCursor(note);
            mTitleText.setText(note.getString(
    	            note.getColumnIndexOrThrow(NotesDbAdapter.KEY_TITLE)));
            mBodyText.setText(note.getString(
                    note.getColumnIndexOrThrow(NotesDbAdapter.KEY_BODY)));
        }
    }
    
    protected void onSaveInstanceState(Bundle outState) {
    		super.onSaveInstanceState(outState);
    	    outState.putLong(NotesDbAdapter.KEY_ROWID, mRowId);
    	}

    	protected void onPause() {
    		super.onPause();
    	    saveState();
    	}

    	protected void onResume() {
    		super.onResume();
    	    populateFields();
    	}

    	private void saveState() {
    		String title = mTitleText.getText().toString();
    	    String body = mBodyText.getText().toString();

    	    if (mRowId == null) {
    	        long id = mDbHelper.createNote(title, body);
    	        if (id > 0) {
    	            mRowId = id;
    	        }
    	    } else {
    	        mDbHelper.updateNote(mRowId, title, body);
    	    }
    	}
}
