package es.uv.videlsol.valenbisi;

import android.content.ContentValues;
import android.content.Context;
import android.database.Cursor;
import android.database.sqlite.SQLiteDatabase;
import android.database.sqlite.SQLiteOpenHelper;
import android.support.annotation.NonNull;

import java.util.ArrayList;
import java.util.List;

/**
 * Created by Marcos on 28/03/2017.
 */

public class ReportDBHelper extends SQLiteOpenHelper {
    private static final String STOP_COLUMN = "stop";
    private static final String SUBJECT_COLUMN = "subject";
    private static final String DESCRIPTION_COLUMN = "description";
    private static final String TYPE_COLUMN = "type";
    private static final String STATUS_COLUMN = "status";

    public ReportDBHelper(Context context) {
        super(context, "reports", null, 1);
    }

    @Override
    public void onCreate(SQLiteDatabase db) {
        db.execSQL(
                "CREATE TABLE reports (" +
                        STOP_COLUMN + " INT NOT NULL," +
                        SUBJECT_COLUMN + " TEXT NOT NULL," +
                        DESCRIPTION_COLUMN + " TEXT NOT NULL," +
                        TYPE_COLUMN + " INT NOT NULL," +
                        STATUS_COLUMN + " INT NOT NULL" +
                ")"
        );
    }

    @Override
    public void onUpgrade(SQLiteDatabase db, int oldVersion, int newVersion) {
        throw new UnsupportedOperationException();
    }

    private ContentValues reportToCV(Report report, boolean withId) {
        ContentValues cv = new ContentValues();
        if (withId) {
            cv.put("ROWID", report.getId());
        }
        cv.put(STOP_COLUMN, report.getStopId());
        cv.put(SUBJECT_COLUMN, report.getSubject());
        cv.put(DESCRIPTION_COLUMN, report.getDescription());
        cv.put(TYPE_COLUMN, report.getType().ordinal());
        cv.put(STATUS_COLUMN, report.getType().ordinal());
        return cv;
    }

    public void saveReport(@NonNull Report report) {
        if (report.getId() < 0) {
            insertReport(report);
        } else {
            updateReport(report);
        }
    }

    public void insertReport(@NonNull Report report) {
        ContentValues cv = reportToCV(report, false);

        SQLiteDatabase db = getWritableDatabase();
        long rowId = db.insert("reports", null, cv);
        db.close();

        report.setId(rowId);
    }

    public void updateReport(@NonNull Report report) {
        ContentValues cv = reportToCV(report, true);

        SQLiteDatabase db = getWritableDatabase();
        db.update("reports", cv, "ROWID = ?", new String[] { Long.toString(report.getId()) });
        db.close();
    }

    public void deleteReport(@NonNull Report report) {
        if (report.getId() < 0) {
            return;
        }

        SQLiteDatabase db = getWritableDatabase();
        db.delete("reports", "ROWID = ?", new String[] { Long.toString(report.getId()) });
        db.close();
    }

    public List<Report> findByStop(@NonNull StopInfo stop) {
        SQLiteDatabase db = getReadableDatabase();
        Cursor cursor = db.rawQuery("SELECT " +
                "ROWID, " +
                SUBJECT_COLUMN + ", " +
                DESCRIPTION_COLUMN + ", " +
                TYPE_COLUMN + ", " +
                STATUS_COLUMN + " " +
                "FROM reports WHERE " + STOP_COLUMN + " = ?",
                new String[] { Integer.toString(stop.getNumber()) });

        ArrayList<Report> list = new ArrayList<>();
        if (cursor.moveToFirst()) {
            do {
                Report report = new Report(stop);
                report.setId(cursor.getLong(0));
                report.setSubject(cursor.getString(1));
                report.setDescription(cursor.getString(2));
                report.setType(Report.Type.values()[cursor.getInt(3)]);
                report.setStatus(Report.Status.values()[cursor.getInt(4)]);
                list.add(report);
            } while (cursor.moveToNext());
        }

        cursor.close();
        db.close();
        return list;
    }

    public Report findById(long id) {
        throw new UnsupportedOperationException();
    }
}
