package es.uv.videlsol.valenbisi;

import android.app.Service;
import android.content.Context;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.BaseAdapter;
import android.widget.ImageView;
import android.widget.TextView;

import java.util.List;

/**
 * Created by Marcos on 28/03/2017.
 */

public class ReportCursorAdapter extends BaseAdapter {

    private final Context context;
    private final List<Report> reports;

    static class ViewHolder {
        ImageView icon;
        TextView subject;
    }

    public ReportCursorAdapter(Context c, List<Report> reports) {
        context = c;
        this.reports = reports;
    }

    @Override
    public int getCount() {
        return reports.size();
    }

    @Override
    public Object getItem(int position) {
        return reports.get(position);
    }

    @Override
    public long getItemId(int position) {
        return reports.get(position).getId();
    }

    @Override
    public View getView(int position, View convertView, ViewGroup parent) {
        ViewHolder holder = null;

        if (convertView == null) { // Si es null la creamos a partir de layout
            LayoutInflater li = (LayoutInflater) context.getSystemService(Service.LAYOUT_INFLATER_SERVICE);
            convertView = li.inflate(R.layout.report_list_entry, null);

            holder = new ViewHolder();
            holder.icon = (ImageView) convertView.findViewById(R.id.report_status_icon);
            holder.subject = (TextView) convertView.findViewById(R.id.report_subject);
            convertView.setTag(holder);
        } else {
            // Si no es null la reutilizamos para actualizarla
            holder = (ViewHolder) convertView.getTag();
        }

        Report report = reports.get(position);
        holder.subject.setText(report.getSubject());
        switch (report.getStatus()) {
            case OPEN:
                holder.icon.setImageResource(R.drawable.report_open);
                break;
            case PROCESSING:
                holder.icon.setImageResource(R.drawable.report_processing);
                break;
            case CLOSED:
                holder.icon.setImageResource(R.drawable.report_closed);
                break;
        }

        return convertView;
    }
}
